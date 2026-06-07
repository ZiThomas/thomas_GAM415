// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"
#include "thomas_GAM415Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APortal::APortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// SET UP DEFAULT SUBOBJECTS FOR THE PORTAL!! 
	// THIS INCLUDES THE MESH COMPONENT, THE BOX COMPONENT, AND THE SCENE CAPTURE COMPONENT!! 
	// THESE COMPONENTS WILL BE USED TO CREATE THE PORTAL EFFECT!! 
	// THE MESH COMPONENT WILL BE USED TO DISPLAY THE PORTAL
	// THE BOX COMPONENT WILL BE USED TO DETECT WHEN THE PLAYER CHARACTER OVERLAPS WITH THE PORTAL
	// THE SCENE CAPTURE COMPONENT WILL BE USED TO RENDER THE VIEW FROM THE OTHER PORTAL!!
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	boxComp = CreateDefaultSubobject<UBoxComponent>("Box Comp");
	sceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>("Capture");
	rootArrow = CreateDefaultSubobject<UArrowComponent>("Root Arrow");
	
	// SET UP ROOT COMPONENT AND ATTACH THE OTHER COMPONENTS TO IT!! 
	// THIS WILL ENSURE THAT THE PORTAL ACTS AS A SINGLE ENTITY IN THE GAME WORLD!!
	RootComponent = boxComp;
	mesh->SetupAttachment(boxComp);
	sceneCapture->SetupAttachment(mesh);
	rootArrow->SetupAttachment(RootComponent);

	// DISBALE COLLISION FOR MESH SO PLAYER CAN WALK THROUGH THE PORTAL!!
	mesh->SetCollisionResponseToAllChannels(ECR_Ignore);
}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();

	boxComp->OnComponentBeginOverlap.AddDynamic(this, &APortal::OnOverlapBegin);
	mesh->SetHiddenInSceneCapture(true);

	if (mat)
	{
		mesh->SetMaterial(0, mat);
	}

	// CHECKING IF MATERIAL IS VALID!! 
	// IF IT IS, SET THE MATERIAL FOR THE MESH COMPONENT TO THE MATERIAL!!
	if (mat)
	{
		mesh->SetMaterial(0, mat);
	}
	
}

// Called every frame
void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// UPDATE THE PORTALS EVERY FRAME TO ENSURE THAT THE PORTAL EFFECT IS WORKING PROPERLY!!
	UpdatePortals();
}


void APortal::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Athomas_GAM415Character* playerChar = Cast<Athomas_GAM415Character>(OtherActor);
	
	//CHECKING TO SEE IF TELEPORTING IS FALSE!! THIS WILL PREVENT THE PLAYER FROM GETTING TELEPORTED BACK AND FORTH BETWEEN THE PORTALS INSTANTLY!!
	if (playerChar)
	{
		if (OtherPortal)
		{
			if (!playerChar->isTeleporting)
			{
				playerChar->isTeleporting = true;
				FVector loc = OtherPortal->rootArrow->GetComponentLocation();
				playerChar->SetActorLocation(loc);

				// TIMER TO SET THE BOOLEAN BACK TO FALSE AFTER 1 SECOND!! THIS WILL ALLOW THE PLAYER TO TELEPORT AGAIN AFTER 1 SECOND!!
				FTimerHandle TimerHandle;
				FTimerDelegate TimerDelegate;
				TimerDelegate.BindUFunction(this, "SetBool", playerChar);
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 1, false);
			}
		}
	}
}

void APortal::SetBool(Athomas_GAM415Character* playerChar)
{
	// CHECKS TO SEE IF PLAYER TELEPORTING IS FALSE!!
	if (playerChar)
	{
		playerChar->isTeleporting = false;
	}
}

void APortal::UpdatePortals()
{

	// GET LOCATION OF THIS PORTAL AND THE OTHER PORTAL!!
	FVector Location = this->GetActorLocation() - OtherPortal->GetActorLocation();
	FVector camLocation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetTransformComponent()->GetComponentLocation();
	FRotator camRotation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetTransformComponent()->GetComponentRotation();
	FVector CombinedLocation = camLocation + Location;

	sceneCapture->SetWorldLocationAndRotation(CombinedLocation, camRotation);

}
