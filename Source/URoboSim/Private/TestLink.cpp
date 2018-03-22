// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLink.h"
#include "Runtime/Engine/Classes/Engine/StaticMeshActor.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/Engine/Brush.h"
#include "Runtime/Engine/Classes/Components/BrushComponent.h"
#include "Editor/UnrealEd/Public/Editor.h"
#include "Editor/UnrealEd/Private/GeomFitUtils.h"
#include "Editor/UnrealEd/Classes/Builders/CubeBuilder.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Editor/UnrealEd/Classes/Editor/EditorEngine.h"
#include "Editor/UnrealEd/Public/EditorModeManager.h"
#include "Runtime/CoreUObject/Public/UObject/UObjectGlobals.h"
#include "Runtime/Engine/Classes/PhysicsEngine/BodySetup.h"
#include "Private/ConvexDecompTool.h"
// Sets default values
ATestLink::ATestLink()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    Root = CreateDefaultSubobject<UStaticMeshComponent>("Root");
    // Root = CreateDefaultSubobject<UBrushComponent>("Root");
    RootComponent = Root;
    static ConstructorHelpers::FObjectFinder<UMaterial> Mat(TEXT("Material'/Game/pr2/lambert2.lambert2'"));
    Material = (UMaterial*)Mat.Object;


}

// Called when the game starts or when spawned
void ATestLink::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void ATestLink::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void ATestLink::PostActorCreated()
{
    Super::PostActorCreated();

    bool bIsAdditive = true;
    UWorld *World = GEditor->GetEditorWorldContext().World();
    UCubeBuilder* BrushBuilder = NewObject<UCubeBuilder>(this,"CubeBuilder");
    BrushBuilder->X = 100;
    BrushBuilder->Y = 200;
    BrushBuilder->Z = 100;
    ABrush* DefBrush = World->GetDefaultBrush();
    DefBrush->BrushBuilder = BrushBuilder;
    DefBrush->BrushBuilder->Build(World, DefBrush);
    // const TCHAR* Command = bIsAdditive ? TEXT("BRUSH ADD SELECTNEWBRUSH") : TEXT("BRUSH SUBTRACT SELECTNEWBRUSH");
    // GEditor->Exec(World, Command);
    DefBrush->SetNeedRebuild(DefBrush->GetLevel());
    GEditor->RebuildAlteredBSP();


    UStaticMesh* NewMesh = CreateStaticMeshFromBrush(this, TEXT("TEST"),GWorld->GetDefaultBrush(), GWorld->GetDefaultBrush()->Brush);


    FStaticMeshLODResources& LODModel = NewMesh->RenderData->LODResources[0];
    int32 NumVerts = LODModel.VertexBuffer.GetNumVertices();
    TArray<FVector> Verts;
    for(int32 i=0; i<NumVerts; i++)
    {
        FVector Vert = LODModel.PositionVertexBuffer.VertexPosition(i);
        Verts.Add(Vert);
    }

    // Grab all indices
    TArray<uint32> AllIndices;
    LODModel.IndexBuffer.GetCopy(AllIndices);

    // Only copy indices that have collision enabled
    TArray<uint32> CollidingIndices;
    for(const FStaticMeshSection& Section : LODModel.Sections)
    {
        if(Section.bEnableCollision)
        {
            for (uint32 IndexIdx = Section.FirstIndex; IndexIdx < Section.FirstIndex + (Section.NumTriangles * 3); IndexIdx++)
            {
                CollidingIndices.Add(AllIndices[IndexIdx]);
            }
        }
    }

    // ClearSelectedPrims();
    FlushRenderingCommands();

    // Get the BodySetup we are going to put the collision into
    UBodySetup* bs = NewMesh->BodySetup;
    if(bs)
    {
        UE_LOG(LogTemp, Warning, TEXT("removed simple collision"));
        bs->RemoveSimpleCollision();
    }
    else
    {
        // Otherwise, create one here.
        UE_LOG(LogTemp, Warning, TEXT("Created new BodySetup."));
        NewMesh->CreateBodySetup();
        bs = NewMesh->BodySetup;
    }


    UE_LOG(LogTemp, Warning, TEXT("Num Verts: %d"), Verts.Num());
    UE_LOG(LogTemp, Warning, TEXT("Num CollidingIndices: %d"), CollidingIndices.Num());

    float InAccuracy = 1.0;
    int32 InMaxHullVerts = 16;

    if(Verts.Num() >= 3 && CollidingIndices.Num() >= 3)
    {
        UE_LOG(LogTemp, Warning, TEXT("Create Convex Haul"));
        DecomposeMeshToHulls(bs, Verts, CollidingIndices, InAccuracy, InMaxHullVerts);
    }
    // refresh collision change back to staticmesh components
    RefreshCollisionChange(*NewMesh);
    Root->SetStaticMesh(NewMesh);
    Root->SetMaterial(0, Material);

}
