// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileActor.generated.h"

UCLASS()
class DEEPERANDDEEPER_API ATileActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATileActor();

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* Root;

	UPROPERTY(EditAnywhere, Category = "Tile")
	class UStaticMeshComponent* FloorMesh;

	UPROPERTY(EditAnywhere, Category = "Tile")
	class UStaticMeshComponent* RoofMesh;

	UPROPERTY(EditAnywhere, Category = "Tile")
	class UStaticMeshComponent* RightWallMesh;

	UPROPERTY(EditAnywhere, Category = "Tile")
	class UStaticMeshComponent* LeftWallMesh;

	UPROPERTY(EditAnywhere, Category = "Tile")
	class UStaticMeshComponent* BarrierMesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Tile")
	class UArrowComponent* NextTileSpawnPoint;

	UPROPERTY(EditAnywhere, Category = "Tile")
	class UArrowComponent* PuzzleSpawnPoint;

	UPROPERTY(EditAnywhere, Category = "Tile")
	class UMaterialInstance* LockedMaterial;

	UPROPERTY(EditAnywhere, Category = "Tile")
	class UMaterialInstance* UnlockedMaterial;

	UPROPERTY(EditDefaultsOnly, Category = "Puzzle")
	class USceneComponent* ButtonLocation;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* DestroyVolume;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* LockVolume;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ATileUnlockButton> UnlockButtonClass;

	UPROPERTY(EditDefaultsOnly)
	class ATileUnlockButton* UnlockButton;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class APuzzle>> PuzzleClasses;

	UFUNCTION(BlueprintCallable)
	void LockTile(bool bLockState);

	FTransform GetNextTileTransform();

	void OnPuzzleComplete();
	void Init();
	void OnUnlockButtonPressed();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void UpdateBarrierCollision();
	void UpdateBarrierMaterial();

	bool bTileLockState = false;

	UFUNCTION()
	void OnLockVolumeOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnDestroyVolumeOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	bool IsPlayerActor(AActor* OtherActor);
};
