// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProcPlane.generated.h"

//FORWARD DECLARATION FOR PROCEDURAL MESH COMPONENT!!
class UProceduralMeshComponent;

UCLASS()
class THOMAS_GAM415_API AProcPlane : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProcPlane();

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
	TArray<FVector2D> UV0;

	//TEXTURE FOR THE PLANE!!
	UPROPERTY(EditAnywhere)
	UMaterialInterface* PlaneMat;

	//FUNCTION TO CREATE THE MESH!!
	UFUNCTION()
	void CreateMesh();

	//POINTER TO THE PROCEDURAL MESH COMPONENT!!
private:
	UProceduralMeshComponent* procMesh;
};
