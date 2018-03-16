// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UnrealEd.h"
#include "RRobotAsset.h"
#include "RFileParser.h"
#include "RFactoryRobotAsset.generated.h"

/**
 *
 */
UCLASS()
class UROBOSIM_API URFactoryRobotAsset : public UFactory, public FReimportHandler
{
    GENERATED_BODY()
public:
    URFactoryRobotAsset(const FObjectInitializer& ObjectInitializer);
    ~URFactoryRobotAsset();
#if WITH_EDITOR
    // Begin UFactory Interface

    /**
     * Generates the RRobotAsset from a Text buffer,
     *
     */
    virtual UObject* FactoryCreateText(UClass* InClass,
            UObject* InParent,
            FName InName,
            EObjectFlags Flags,
            UObject* Context,
            const TCHAR* Type,
            const TCHAR*& Buffer,
            const TCHAR* BufferEnd,
            FFeedbackContext* Warn) override;

    /** True if it supports this class. */
    virtual bool DoesSupportClass(UClass* Class) override;

    // End UFactory Interface


    // Begin FReimportHandler interface

    /*
     * Functions of the ReimportHandler (override). Allows reimporting via drag and drop.
     */
    virtual bool FactoryCanImport(const FString& Filename) override;
    virtual bool CanReimport(UObject* Object, TArray<FString>& OutFilenames) override;
    virtual void SetReimportPaths(UObject* Object, const TArray<FString>& NewReimportPaths) override;
    virtual EReimportResult::Type Reimport(UObject* Object) override;

    // End FReimportHandler interface

    /** Loads information for Reimport.
     * @param ForAsset Holds the Information for reimport.
     * @return true if data could be loaded. Otherwise false.
     */
    bool ImportSourceFile(class URobotAsset* ForAsset) const;



    bool CreateFileParser();
    /** Edits Xml and loads .fbx files.
     * @param ConvertXml Holds the xml content (URDF).
     * @param Flags Flags of the action.
     * @param InOuter To save the location.
     * @return true if data could be loaded. Otherwise false.
     */

    // To decide whether it is a reimport.
    bool bIsReimport;

protected:
    URFileParser* FileParser;
#endif
};
