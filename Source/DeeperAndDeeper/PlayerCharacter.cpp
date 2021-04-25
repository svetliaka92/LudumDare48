// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FPCamera"));
	FirstPersonCameraComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerController = Controller;
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// raycast for interactable
	// if one is found - enable crosshair
	if (TraceForInteractable())
	{
		EnableCrosshair(true);
	}
	else
	{
		EnableCrosshair(false);
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerCharacter::Interact);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &APlayerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &APlayerCharacter::LookUpAtRate);
}

bool APlayerCharacter::TraceForInteractable()
{
	if (PlayerController == nullptr)
		return false;

	FHitResult Hit;
	FVector Location;
	FRotator Rotation;
	PlayerController->GetPlayerViewPoint(Location, Rotation);
	FVector End = Location + Rotation.Vector() * Reach;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	if (GetWorld()->LineTraceSingleByChannel(
		Hit,
		Location,
		End,
		ECollisionChannel::ECC_GameTraceChannel2,
		Params
	))
	{
		// check if the component hit is an interactable
		IIInteractable* InteractableHit = Cast<IIInteractable>(Hit.Component);
		if (InteractableHit == nullptr)
		{
			// if the component hit is not an interactable, chech its owning actor
			InteractableHit = Cast<IIInteractable>(Hit.Actor);
		}

		if (InteractableHit != nullptr)
		{
			Interactable = InteractableHit;
			return true;
		}
	}
	else
	{
		Interactable = nullptr;
		return false;
	}

	return false;
}

void APlayerCharacter::Interact()
{
	if (Interactable != nullptr)
	{
		Interactable->Interact();
	}
}

void APlayerCharacter::EnableCrosshair(const bool bState)
{
	if (bState)
	{
		if (bCrosshairState)
			return;

		bCrosshairState = bState;
		// enable crosshair
	}
	else
	{
		if (!bCrosshairState)
			return;

		bCrosshairState = bState;
		// disable crosshair
	}
}

void APlayerCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void APlayerCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}
