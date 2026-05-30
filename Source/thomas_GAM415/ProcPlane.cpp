// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcPlane.h"
#include "ProceduralMeshComponent.h"

// Sets default values
AProcPlane::AProcPlane()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; //CHANGED BECAUSE WE DON'T NEED TO TICK EVERY FRAME!!

	//ESTABLISHING DEFAULT SUBOBJECT FOR THE PROCEDURAL MESH COMPONENT!!
	procMesh = CreateDefaultSubobject<UProceduralMeshComponent>("Proc Mesh");
}

// Called when the game starts or when spawned
void AProcPlane::BeginPlay()
{
	Super::BeginPlay();
	
}
//CALLED BEFORE WE LOAD INTO THE GAME, SO WE CAN CREATE THE MESH BEFOREHAND!!
void AProcPlane::PostActorCreated()
{
	Super::PostActorCreated();
	CreateMesh();

	//IF STATEMENT TO CHECK IF THE MATERIAL IS VALID, THEN SET THE MATERIAL FOR THE PLANE!!
	if (PlaneMat)
	{
		procMesh->SetMaterial(0, PlaneMat);
	}
}
//CALLED AFTER WE LOAD INTO THE GAME, SO WE CAN CREATE THE MESH IF WE MAKE CHANGES TO IT IN THE EDITOR!!
void AProcPlane::PostLoad()
{
	Super::PostLoad();
	CreateMesh();

	//IF STATEMENT TO CHECK IF THE MATERIAL IS VALID, THEN SET THE MATERIAL FOR THE PLANE!!
	if (PlaneMat)
	{
		procMesh->SetMaterial(0, PlaneMat);
	}
}

// Called every frame
void AProcPlane::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
//FUNCTION TO CREATE THE MESH!!
void AProcPlane::CreateMesh()
{
	procMesh->CreateMeshSection(0, Vertices, Triangles, TArray<FVector>(), UV0, TArray<FColor>(), TArray<FProcMeshTangent>(), true);
}

