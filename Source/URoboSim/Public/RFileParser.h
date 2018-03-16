// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IURoboSim.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Runtime/XmlParser/Public/FastXml.h"
#include "RFileParser.generated.h"

UCLASS()
class UROBOSIM_API URElement : public UObject
{
    GENERATED_BODY()
public:
    URElement(){};
    TMap<FString, FString> Elements;
    TMap<FString,FString> Attributs;
    TMap<FString, URElement*> ChildElements;

    void AddElement(FString Key, FString Value);
    void AddAttribute(FString Key, FString Value);
    void AddChildElement(FString Key, URElement* Child);
    URElement* AddElementOrChild(FString Key, FString Value);
};

class UROBOSIM_API FRFileParserCallback : public IFastXmlCallback
{
public:
    FRFileParserCallback();
    virtual ~FRFileParserCallback();
    class URFileParser* Owner;
    TArray<URElement*>& GetComponentList();

protected:
    bool ProcessAttribute(const TCHAR* AttributeName, const TCHAR* AttributeValue) override;

    /** Called when an element's scope ends in the XML file.
     * Use the stack and the map to pass the information to the robot and build the links and joints accordingly.
     * @param ElementName Name of the element which ends.
     * @return true if successful, false otherwise.
     */
    bool ProcessClose(const TCHAR* ElementName);

    /** Called when a comment is encountered. This can happen pretty much anywhere in the file.
     * Always true because for RRobot comments are unimportant.
     * @param Comment The Comment
     * @return always true.
     */
    bool ProcessComment(const TCHAR* Comment);

    /** Called when a new XML element is encountered, starting a new scope.
     * @param ElementName Name of the Element.
     * @param ElementData
     * @param XmlFileLineNumber Line of the xml
     * @return true if successful, false otherwise.
     */
    bool ProcessElement(const TCHAR* ElementName, const TCHAR* ElementData, int32 XmlFileLineNumber);

    /** Called after XML header is parsed.
     * @param ElementData
     * @param XmlFileLineNumber
     * @return always true.
     */
    bool ProcessXmlDeclaration(const TCHAR* ElementData, int32 XmlFileLineNumber);

    URElement* AddElementToComponentList();
    void DeleteElement(FString Element);

	/** Stack to Save the current Element.*/
	TArray<FString> Stack;
    TMap<FString, FString> AttMap;
    TArray<URElement*> ComponentList;
    URElement* CurrentElement;

};


/**
 *
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UROBOSIM_API URFileParser : public UObject
{
    GENERATED_BODY()
public:
    URFileParser();
    ~URFileParser(){};

    virtual void ParseFile();
    void SetTextToParse(FString InTextToParse);
    FString GetTextToParse();

    /** Edits Xml and loads .fbx files.
     * @param ConvertXml Holds the xml content (URDF).
     * @param Flags Flags of the action.
     * @param InOuter To save the location.
     * @return true if data could be loaded. Otherwise false.
     */
    FString AdeptXml(const FString PathToXml, const FString ConvertXml, const EObjectFlags Flags, UObject* InOuter) const;

    FRFileParserCallback Callback;
    FString TextToParse;
    TArray<URElement*> GetComponentList();
};


