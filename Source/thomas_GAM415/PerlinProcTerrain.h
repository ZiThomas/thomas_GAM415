// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PerlinProcTerrain.generated.h"

// FORWARD DECLARATIONS!!
class UProceduralMeshComponent;
class UMaterialInterface;

UCLASS()
class THOMAS_GAM415_API APerlinProcTerrain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APerlinProcTerrain();

	// VARIABLES TO GENERATE SIZE OF LANDSCAPE WITH MINIMAL SIZE OF 0!!
	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0))
	int XSize = 0;

	UPROPERTY(EditAnywhere, Meta = (CLampMin = 0))
	int YSize = 0;

	// MULTIPLY THE HEIGHT OF "NOISE" TO MAKE THE LANDSCAPE TALLER OR FLATTER!!
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ClampMin = 0))
	float ZMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0))
	float NoiseScale = 1.0f;

	// ADJUST THE SCALE OF THE LANDSCAPE!! MINIMAL SIZE OF 0.000001 TO PREVENT CRASHING!!
	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0.000001))
	float Scale = 0;

	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0.000001))
	float UVScale = 0;

	// ADJUST HOW BIG AND DEEP THE HOLES IN THE LANDSCAPE ARE!! MINIMAL SIZE OF 0.000001 TO PREVENT CRASHING!!
	UPROPERTY(EditAnywhere)
	float radius;

	UPROPERTY(EditAnywhere)
	FVector Depth;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// APPLY MATERIAL TO THE LANDSCAPE!!
	UPROPERTY(EditAnywhere)
	UMaterialInterface* Mat;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// CALL TO ALTER THE MESH!!
	UFUNCTION()
	void AlterMesh(FVector impactPoint);

private:
	// POINTER TO THE PROCEDURAL MESH COMPONENT!!
	UProceduralMeshComponent* ProcMesh;
	TArray<FVector> Vertices;
	TArray<int> Triangles;
	TArray<FVector2D> UV0;
	TArray<FVector> Normals;
	TArray<FColor> UpVertexColors;

	int sectionID = 0;

	// GENERATE THE VERTICES AND TRIANGLES FOR THE LANDSCAPE!!
	void CreateVertices();
	void CreateTriangles();
};
