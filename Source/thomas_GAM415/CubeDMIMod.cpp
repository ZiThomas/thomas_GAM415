// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeDMIMod.h"
#include "thomas_GAM415Character.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ACubeDMIMod::ACubeDMIMod()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// SET UP COMPONENTS FOR THE CUBE!!
	boxComp = CreateDefaultSubobject<UBoxComponent>("Box Component");
	cubeMesh = CreateDefaultSubobject<UStaticMeshComponent>("Cube Mesh");

	RootComponent = boxComp;
	cubeMesh->SetupAttachment(boxComp);

}

// Called when the game starts or when spawned
void ACubeDMIMod::BeginPlay()
{
	Super::BeginPlay();
	

	boxComp->OnComponentBeginOverlap.AddDynamic(this, &ACubeDMIMod::OnOverlapBegin);

	if (baseMat)
	{
		dmiMat = UMaterialInstanceDynamic::Create(baseMat, this); 
	}

	if (cubeMesh)
	{
		cubeMesh->SetMaterial(0, dmiMat);
	}
}

// Called every frame
void ACubeDMIMod::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACubeDMIMod::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//CHECKING TO SEE IF THE OTHER ACTOR IS THE PLAYER!!
	Athomas_GAM415Character* overlappedActor = Cast<Athomas_GAM415Character>(OtherActor);

	if (overlappedActor)
	{
		float rannumX = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f);
		float rannumY = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f);
		float rannumZ = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f);

		FVector4 randColor = FVector4(rannumX, rannumY, rannumZ, 1.f);
		if (dmiMat)
		{
			dmiMat->SetVectorParameterValue("Color", randColor);
			dmiMat->SetScalarParameterValue("Darkness", rannumX);
		}
	}
}

