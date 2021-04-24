// Fill out your copyright notice in the Description page of Project Settings.


#include "TileActor.h"
#include "TileUnlockButton.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "InfinitePuzzlesMode.h"
#include "GameFramework/Character.h"
#include "Puzzle.h"

// Sets default values
ATileActor::ATileActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor"));
	FloorMesh->SetupAttachment(RootComponent);

	RoofMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Roof"));
	RoofMesh->SetupAttachment(RootComponent);

	RightWallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallRight"));
	RightWallMesh->SetupAttachment(RootComponent);

	LeftWallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallLeft"));
	LeftWallMesh->SetupAttachment(RootComponent);

	BarrierMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Barrier"));
	BarrierMesh->SetupAttachment(RootComponent);

	NextTileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("NextTileSpawnPoint"));
	NextTileSpawnPoint->SetupAttachment(RootComponent);

	PuzzleSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("PuzzleSpawnPoint"));
	PuzzleSpawnPoint->SetupAttachment(RootComponent);

	ButtonLocation = CreateDefaultSubobject<USceneComponent>(TEXT("ButtonLocation"));
	ButtonLocation->SetupAttachment(RootComponent);

	DestroyVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("DestroyVolume"));
	DestroyVolume->SetupAttachment(RootComponent);

	LockVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("LockVolume"));
	LockVolume->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATileActor::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void ATileActor::Init()
{
	// lock tile
	LockTile(true);

	if (LockVolume != nullptr)
	{
		LockVolume->OnComponentBeginOverlap.AddDynamic(this, &ATileActor::OnLockVolumeOverlap);
	}

	if (DestroyVolume != nullptr)
	{
		DestroyVolume->OnComponentBeginOverlap.AddDynamic(this, &ATileActor::OnDestroyVolumeOverlap);
	}

	// spawn puzzle button
	if (UnlockButtonClass != nullptr)
	{
		UnlockButton = GetWorld()->SpawnActor<ATileUnlockButton>(UnlockButtonClass);
		if (UnlockButton != nullptr)
		{
			UnlockButton->SetActorLocation(ButtonLocation->GetComponentTransform().GetLocation());
			UnlockButton->SetActorRotation(ButtonLocation->GetComponentTransform().GetRotation());

			// TODO - TEMP CODE - change to false
			UnlockButton->Init(this);
			UnlockButton->SetButtonEnableState(true);
		}
	}

	if (PuzzleClasses.Num() >= 1)
	{
		// spawn a random puzzle
		int32 SpawnPuzzleIndex = FMath::RandRange(0, PuzzleClasses.Num() - 1);
		if (PuzzleClasses[SpawnPuzzleIndex])
		{
			APuzzle* SpawnedPuzzle = GetWorld()->SpawnActor<APuzzle>(PuzzleClasses[SpawnPuzzleIndex]);
			if (SpawnedPuzzle)
			{
				// place puzzle at spawn position
				FVector PuzzleLocation = PuzzleSpawnPoint->GetComponentTransform().GetLocation();
				FRotator PuzzleRotation = PuzzleSpawnPoint->GetComponentTransform().GetRotation().Rotator();

				SpawnedPuzzle->SetActorLocation(PuzzleLocation);
				SpawnedPuzzle->SetActorRotation(PuzzleRotation);

				// init the puzzle with this tile as its parent
				SpawnedPuzzle->Init(this);
			}
		}
	}
}

void ATileActor::OnPuzzleComplete()
{
	// enable tile unlock button
	
}

void ATileActor::OnUnlockButtonPressed()
{
	LockTile(false);
}

void ATileActor::LockTile(bool bLockState)
{
	// set tile lock state
	bTileLockState = bLockState;
	// update barrier collision and material
	UpdateBarrierCollision();
	UpdateBarrierMaterial();
}

void ATileActor::UpdateBarrierCollision()
{
	// if lock state is true
	// set collision preset to block everything
	// else set collision preset to trigger
	if (bTileLockState)
	{
		BarrierMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
	else
	{
		BarrierMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ATileActor::UpdateBarrierMaterial()
{
	// if lock state is true
	// set material to opaque red
	// else set to transparent green
	if (bTileLockState)
	{
		BarrierMesh->SetMaterial(0, LockedMaterial);
	}
	else
	{
		BarrierMesh->SetMaterial(0, UnlockedMaterial);
	}
}

FTransform ATileActor::GetNextTileTransform()
{
	return NextTileSpawnPoint->GetComponentTransform();
}

void ATileActor::OnLockVolumeOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
	)
{
	if (IsPlayerActor(OtherActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("On LockVolumeOverlap"));
		LockTile(true);
	}
}

void ATileActor::OnDestroyVolumeOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
	)
{
	if (IsPlayerActor(OtherActor))
	{
		// tell the game mode to spawn another tile
		AInfinitePuzzlesMode* GameMode = Cast<AInfinitePuzzlesMode>(UGameplayStatics::GetGameMode(GetWorld()));
		if (GameMode != nullptr)
		{
			GameMode->SpawnTile();
		}
		if (UnlockButton)
		{
			UnlockButton->Destroy();
		}
		Destroy();
	}
}

bool ATileActor::IsPlayerActor(AActor* OtherActor)
{
	AActor* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (OtherActor == Player)
		return true;

	return false;
}
