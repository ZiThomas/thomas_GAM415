// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "Portal.generated.h"

// FORWARD DECLARATION TO ACCESS PLAYER CHARACTER!!
class Athomas_GAM415Character;

UCLASS()
class THOMAS_GAM415_API APortal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// VARIABLES FOR THE PORTAL!!
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneCaptureComponent2D* sceneCapture;

	UPROPERTY(EditAnywhere)
	UArrowComponent* rootArrow;

	// RENDER TARGET FOR THE SCENE CAPTURE COMPONENT TO RENDER TO ANOTHER REDER TARGET!! THIS IS WHAT WILL BE DISPLAYED ON THE PORTAL MESH!!
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextureRenderTarget2D* renderTarget;

	UPROPERTY(EditAnywhere)
	UBoxComponent* boxComp;

	// POINTER TO THE OTHER PORTAL!! THIS WILL BE USED TO LINK THE TWO PORTALS TOGETHER!!
	UPROPERTY(EditAnywhere)
	APortal* OtherPortal;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* mat;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void SetBool(Athomas_GAM415Character* playerChar);

	UFUNCTION()
	void UpdatePortals();
};
