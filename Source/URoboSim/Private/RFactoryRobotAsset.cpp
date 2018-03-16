// Fill out your copyright notice in the Description page of Project Settings.


#include "RFactoryRobotAsset.h"
#include "IURoboSim.h"
#include "Factories/FbxFactory.h"
#include "AssetRegistryModule.h"

URFactoryRobotAsset::URFactoryRobotAsset(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    // If the factory can currently create a new object from scratch.
    bCreateNew = false;

    // True if the factory imports objects from text.
    bText = true;

    // True if the factory imports objects from files.
    bEditorImport = true;

    // Tells the Editor which file types we can import.
    Formats.Add(TEXT("xml;XML Files"));
    Formats.Add(TEXT("sdf;SDF Files"));

    // Tells the Editor which Asset type this UFactory can import.
    SupportedClass = URobotAsset::StaticClass();

    // Increases the factory priority.
    ImportPriority = DefaultImportPriority - 1;

    // For reimport.
    bIsReimport = false;
}

URFactoryRobotAsset::~URFactoryRobotAsset()
{
}

UObject* URFactoryRobotAsset::FactoryCreateText(UClass* InClass,
        UObject* InParent,
        FName InName,
        EObjectFlags Flags,
        UObject* Context,
        const TCHAR* Type,
        const TCHAR*& Buffer,
        const TCHAR* BufferEnd,
        FFeedbackContext* Feed)
{
    if(DoesSupportClass(InClass))
    {
        CreateFileParser();
    }
    else
    {
        return nullptr;
    }

        // FileParser = new<FRFileParser>();

    // For reimport via import button.
    TArray <FAssetData> SelectionList;

    FString PathPart, FilenamePart, ExtensionPart;
    FPaths::Split(InParent->GetPathName(), PathPart, FilenamePart, ExtensionPart);

    FAssetRegistryModule& AssetRegistryModule
        = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
    IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();
    AssetRegistry.GetAssetsByPath(*PathPart, SelectionList, false, false);

    URobotAsset* NewObjectAsset = NewObject<URobotAsset>(InParent, InName, Flags | RF_Transactional);

    if (SelectionList.Num() != 0) {
        for (auto Item : SelectionList) {
            if (Item.ObjectPath.IsEqual(*(NewObjectAsset->GetPathName(nullptr)))) {
                bIsReimport = true;
                break;
            }
        }
    }
    FileParser->SetTextToParse(FileParser->AdeptXml(FPaths::GetPath(GetCurrentFilename()), Buffer, Flags, InParent));
    FileParser->ParseFile();
    TArray<URElement*> ComponentList = FileParser->GetComponentList();

    CleanUp();
    // Factory only generates reimports (drag and drop, import button creates new factory).
    //TODO check if this is actual true
    UE_LOG(LogTemp, Warning, TEXT("Use FactoryCreateText"));
    bIsReimport = true;

    return NewObjectAsset;
}

bool URFactoryRobotAsset::CreateFileParser()
{
    FileParser = NewObject<URFileParser>(this);
    if(FileParser)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool URFactoryRobotAsset::DoesSupportClass(UClass* Class)
{
    return Class->IsChildOf(SupportedClass);
}

bool URFactoryRobotAsset::FactoryCanImport(const FString & Filename)
{
    return (Filename.EndsWith(".xml", ESearchCase::IgnoreCase)) ? true : Filename.EndsWith(".sdf", ESearchCase::IgnoreCase);
}

bool URFactoryRobotAsset::CanReimport(UObject* Object, TArray<FString>& OutFilenames)
{
    // URobotAsset* Asset = Cast<URobotAsset>(Object);
    // if (Asset)
    // {
    //     const FString &Filename = Asset->GetAssetFilename();
    //     if (!Filename.IsEmpty())
    //     {
    //         OutFilenames.Add(Filename);
    //     }
    //
    //     return true;
    // }
    return false;
}

void URFactoryRobotAsset::SetReimportPaths(UObject* Object, const TArray<FString>& NewReimportPaths)
{
    // URobotAsset* Asset = Cast<URobotAsset>(Object);
    //
//     if (Asset && ensure(NewReimportPaths.Num() == 1))
//     {
//         Asset->SetAssetFilename(NewReimportPaths[0]);
//
//         // For reimport in a new session (Editor - Drag and drop).
//         bIsReimport = true;
//     }
}

EReimportResult::Type URFactoryRobotAsset::Reimport(UObject* Object)
{
    // if (ImportSourceFile(Cast<URobotAsset>(Object)))
    // {
    //     // Find the outer package so we cam make it dirty.
    //     if (Object->GetOuter())
    //     {
    //         Object->GetOuter()->MarkPackageDirty();
    //     }
    //     else
    //     {
    //         Object->MarkPackageDirty();
    //     }
    //     return EReimportResult::Succeeded;
    // }
    // else
    // {
    //     return EReimportResult::Failed;
    // }
    return EReimportResult::Succeeded;
}

bool URFactoryRobotAsset::ImportSourceFile(URobotAsset* ForAsset) const
{

    // FString AssetFilename = ForAsset->GetAssetFilename();
    // if (ForAsset == nullptr || AssetFilename.IsEmpty())
    // {
    //     return false;
    // }
    //
    // FString ReadString;
    // if (!FFileHelper::LoadFileToString(ReadString, *AssetFilename, FFileHelper::EHashOptions::None))
    // {
    //     return false;
    // }
    // // Passing the XML.
    // ForAsset->SetXml(AdeptXml(FPaths::GetPath(AssetFilename),
    //             ReadString, ForAsset->GetFlags(), ForAsset->GetOuter()));

    return true;
}



