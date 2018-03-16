// Fill out your copyright notice in the Description page of Project Settings.


#include "RFileParser.h"
#include "Factories/FbxFactory.h"


URFileParser::URFileParser()
{
    Callback.Owner= this;
}

void URElement::AddElement(FString Key, FString Value)
{
    Elements.Add(Key, Value);
}

void URElement::AddAttribute(FString Key, FString Value)
{

    Attributs.Add(Key, Value);
}

void URElement::AddChildElement(FString Key, URElement* Child)
{
    ChildElements.Add(Key, Child);
}

URElement* URElement::AddElementOrChild(FString Key, FString Value)
{

    if(Value.IsEmpty())
    {
        URElement* Child = NewObject<URElement>(this);
        AddChildElement(Key, Child);
        return Child;
    }
    else
    {
        AddAttribute(Key, Value);
        return this;
    }
}



FRFileParserCallback::FRFileParserCallback()
{

}

FRFileParserCallback::~FRFileParserCallback()
{

}


TArray<URElement*>& FRFileParserCallback::GetComponentList()
{
    return ComponentList;
}

URElement* FRFileParserCallback::AddElementToComponentList()
{
    URElement* Element = NewObject<URElement>(Owner);
    ComponentList.Emplace(Element);
    return Element;
}

void FRFileParserCallback::DeleteElement(FString Element)
{
    FString el = Stack.Pop();
    while(!el.Equals(Element))
    {
        el = Stack.Pop();
    }
}

bool FRFileParserCallback::ProcessAttribute(const TCHAR* AttributeName, const TCHAR* AttributeValue)
{
    FString AttName(AttributeName);
    FString AttValue(AttributeValue);
    AttMap.Add(AttName,AttValue);
    return true;
}

bool FRFileParserCallback::ProcessClose(const TCHAR* ElementName)
{
    FString ElemName =FString(ElementName);
    if(ElemName.Equals("link") ||
       ElemName.Equals("joint"))
    {
        // for (auto & el : AttMap)
        // {
        //     UE_LOG(LogTemp, Log, TEXT("%s : %s"), *el.Key, *el.Value);
        // }
        DeleteElement(FString(ElementName));

    }

    return true;
}



bool FRFileParserCallback::ProcessComment(const TCHAR* Comment)
{
    return true;
}

bool FRFileParserCallback::ProcessElement(const TCHAR* ElementName, const TCHAR* ElementData, int32 XmlFileLineNumber)
{
    FString ElemName = FString(ElementName);
    FString ElemData = FString(ElementData);
    if(ElemName.Equals("joint") || ElemName.Equals("link"))
    {
        // if(FString(ElementData).IsEmpty())
        // {
        //     UE_LOG(LogTemp, Log, TEXT("Empty"));
        // }
        Stack.Empty();
        AttMap.Empty();
        Stack.Push(ElemName);
        CurrentElement = AddElementToComponentList();
        return true;
    }
    else if((Stack.Contains("joint") || Stack.Contains("link"))
            && !ElemName.IsEmpty())
    {
        // UE_LOG(LogTemp, Log, TEXT("Component:%s, ElementName:%s"), *ComponentList.Last()->Elements["name"], *ElemName);

        CurrentElement = CurrentElement->AddElementOrChild(ElemName, ElemData);
        Stack.Emplace(ElemName);
        return true;
    }
    else if(!ElemName.IsEmpty())
    {
        Stack.Emplace(ElemName);
        return true;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to read an element in robot description.\n"));
        return false;
    }
}

bool FRFileParserCallback::ProcessXmlDeclaration(const TCHAR* ElementData, int32 XmlFileLineNumber)
{
    return true;
}

void URFileParser::SetTextToParse(FString InTextToParse)
{
    TextToParse=InTextToParse;
}

FString URFileParser::GetTextToParse()
{
    return TextToParse;
}

TArray<URElement*> URFileParser::GetComponentList()
{
    return Callback.GetComponentList();
}

void URFileParser::ParseFile()
{
    FText Error = NSLOCTEXT("RFastXmlCallbackRobotError", "FFastXmlError", "Error in the execution of the XML-Parser");
    // Default Line for OutErrorLineNumber
    int32 LineNumb = -1;

    bool Success;
    // Remove linebreaks and tabs
    //TextToParse = TextToParse.Trim().TrimTrailing();
    TextToParse.TrimStartAndEndInline();
    TextToParse = TextToParse.Replace(L"\n", L" ");
    TextToParse = TextToParse.Replace(L"\r", L"");
    TextToParse = TextToParse.Replace(L"\t", L" ");

    if (TextToParse.IsEmpty())
    {
        return;
    }

    Success = FFastXml::ParseXmlFile((IFastXmlCallback*)&Callback, TEXT(""), TextToParse.GetCharArray().GetData(), nullptr, false, false, Error, LineNumb);

    UE_LOG(LogTemp, Warning, TEXT("Use Paser function to parse URDF"));
    if (!Success)
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to create Robot\n"));
    }
}


FString URFileParser::AdeptXml(const FString PathToXml,
        const FString ConvertXml, const EObjectFlags Flags,
        UObject* InOuter) const
{
    //To create the uAsset meshes from .fbx.
    TMap<FString, FString> MeshMap;

    // New XML has the adapted UAsset path and is used for building.
    FString NewXml = "";

    TArray<FString> XMLInLines;
    FString(ConvertXml).ParseIntoArrayLines(XMLInLines, TEXT(">"));
    bool bInComment = false;

    for (FString Line : XMLInLines) {

        // Checks if .fbx is in a comment.
        if (Line.Contains("<!--")) {
            bInComment = true;
        }
        if (Line.Contains("-->")) {
            bInComment = false;
        }

        if (Line.Contains("mesh filename") && (Line.Contains("fbx") || Line.Contains("stl") || Line.Contains("dae"))&& !bInComment) {

            // Standardizes the file paths for the Xml
            Line = Line.Replace((L"\\"), (L"/"), ESearchCase::IgnoreCase);
            Line = Line.Replace((L"package://"), (L"/"), ESearchCase::IgnoreCase);
            Line = Line.Replace((L".stl"), (L".fbx"), ESearchCase::IgnoreCase);
            Line = Line.Replace((L".dae"), (L".fbx"), ESearchCase::IgnoreCase);
            FString SaveLine = Line;

            // Delete everything before the path.
            Line.RemoveAt(0, Line.Find("\"") + 1, true);

            FString PathToFbx = Line;

            // Deletes information to get the path.
            Line.RemoveAt(0, Line.Find("\""), true);
            PathToFbx = PathToFbx.Replace(*Line, (L""), ESearchCase::IgnoreCase);

            // FString that stores the mesh name. Only fbx files are allowed.
            FString FbxName = FPaths::GetBaseFilename(PathToFbx, true);

            // New Path for the UAsset.
            FString AssetPath = InOuter->GetPathName() + "/" + FbxName + "." + FbxName;

            // Replaces the old path to the fbx to the new fbx.
            SaveLine = SaveLine.Replace(*PathToFbx, *AssetPath, ESearchCase::IgnoreCase);

            Line = SaveLine;

            if (!MeshMap.Contains(FbxName)) {

                // if for /Meshes/myfbx,fbx ... else for full path
                int32 Index = 0;
                if (PathToFbx.StartsWith(FString("/"), ESearchCase::IgnoreCase)) {

                    MeshMap.Add(FbxName, PathToXml + PathToFbx);
                }
                else {
                    MeshMap.Add(FbxName, PathToFbx);
                }
            }
        }
        // Creates the new XML.
        NewXml = NewXml + Line + "\n";
    }
    // Return the new Xml.
    return NewXml;
}
