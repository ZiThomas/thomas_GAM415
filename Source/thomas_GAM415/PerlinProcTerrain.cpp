// Fill out your copyright notice in the Description page of Project Settings.


#include "PerlinProcTerrain.h"
#include "ProceduralMeshComponent.h"
#include "KismetProceduralMeshLibrary.h"

// Sets default values
APerlinProcTerrain::APerlinProcTerrain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// SET UP DEFAULT SUBOBJECT FOR THE PROCEDURAL MESH COMPONENT!! ATTACH IT TO THE ROOT COMPONENT!!
	ProcMesh = CreateDefaultSubobject<UProceduralMeshComponent>("Procedural Mesh");
	ProcMesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void APerlinProcTerrain::BeginPlay()
{
	Super::BeginPlay();
	
	// GENERATE THE VERTICES AND TRIANGLES FOR THE LANDSCAPE, THEN CREATE THE MESH SECTION FOR THE PROCEDURAL MESH COMPONENT USING THAT DATA!! THEN SET THE MATERIAL FOR THE LANDSCAPE IF IT'S VALID!!
	CreateVertices();
	CreateTriangles();
	ProcMesh->CreateMeshSection(sectionID, Vertices, Triangles, Normals, UV0, UpVertexColors, TArray<FProcMeshTangent>(), true);
	ProcMesh->SetMaterial(0, Mat);
}

// Called every frame
void APerlinProcTerrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APerlinProcTerrain::AlterMesh(FVector impactPoint)
{
	// PASSING IN THE IMPACT POINT, CHECKING WHICH VERTICES ARE WITHIN THE RADIUS OF THE IMPACT POINT, THEN LOWERING THOSE VERTICES BY THE DEPTH VALUE AND UPDATING THE MESH SECTION WITH THE NEW VERTEX DATA!!
	for (int i = 0; i < Vertices.Num(); i++)
	{
		FVector tempVector = impactPoint - this->GetActorLocation();

		if (FVector(Vertices[i] - tempVector).Size() < radius)
		{
			Vertices[i] = Vertices[i] - Depth;
			ProcMesh->UpdateMeshSection(sectionID, Vertices, Normals, UV0, UpVertexColors, TArray<FProcMeshTangent>());
		}
	}
}

void APerlinProcTerrain::CreateVertices()
{
	// CREATE LOOP TIL X AND Y EQUALT TO XSIZE AND YSIZE!!
	for (int X = 0; X <= XSize; X++)
	{
		for (int Y = 0; Y <= YSize; Y++)
		{
			// PERLIN NOISE GENERATE RANDOM SCALE SIZE!!
			float Z = FMath::PerlinNoise2D(FVector2D(X * NoiseScale + 0.1, Y * NoiseScale + 0.1)) * ZMultiplier;
			GEngine->AddOnScreenDebugMessage(-1, 999.0f, FColor::Yellow, FString::Printf(TEXT("Z: %f"), Z));
			Vertices.Add(FVector(X * Scale, Y * Scale, Z));
			UV0.Add(FVector2D(X * UVScale, Y * UVScale));
		}
	}
}

void APerlinProcTerrain::CreateTriangles()
{
	// CALCULATING WHICH VERTICES TO CONNECT TO MAKE THE TRIANGLES FOR THE LANDSCAPE!! TWO TRIANGLES PER SQUARE!!
	int Vertex = 0;

	for (int Y = 0; Y < YSize; Y++)
	{
		Triangles.Add(Vertex);
		Triangles.Add(Vertex + 1);
		Triangles.Add(Vertex + YSize + 1);
		Triangles.Add(Vertex + 1);
		Triangles.Add(Vertex + YSize + 2);
		Triangles.Add(Vertex + YSize + 1);

		Vertex++;
	}
	
	Vertex++;
}

