// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "ProcMeshFromStatic.generated.h"

UCLASS()
class THOMAS_GAM415_API AProcMeshFromStatic : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProcMeshFromStatic();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//CALL CREATE MESH FUNCTION BEFORE WE LOAD INTO GAME!!

	virtual void PostActorCreated() override;

	virtual void PostLoad() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//VARIABLES FOR THE PROCEDURAL MESH COMPONENT!!
	UPROPERTY(EditAnywhere)
	TArray<FVector> Vertices;

	UPROPERTY(EditAnywhere)
	TArray<int> Triangles;

	UPROPERTY(EditAnywhere)
	TArray<FVector> Normals;

	TArray<FVector2d> UV0;

	UPROPERTY()
	TArray<FLinearColor> VertexColors;

	TArray<FColor> UpVertexColors;

	TArray<FProcMeshTangent> Tangents;

	UPROPERTY(EditANywhere)
	UStaticMeshComponent* baseMesh;

private:
	UProceduralMeshComponent* procMesh;
	void GetMeshData();
	void CreateMesh();
};
