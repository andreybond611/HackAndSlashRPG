// Copyright 2021 Andrey Bondarenko. All rights reserved


#include "Characters/BaseCharacter.h"

#include "Components/CapsuleComponent.h"
#include "HackAndSlashRPG/Public/Components/CommandExecutorComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);

	CommandExecutor = CreateDefaultSubobject<UCommandExecutorComponent>(TEXT("CommandExecutor"));
}

void ABaseCharacter::StartRotating(AActor* Target, bool StopWhenFaceTarget)
{
	bIsRotating = true;
	
	const FVector DiffVector = Target->GetActorLocation() - GetActorLocation();
	const FRotator LookAtRotation = FRotator(0.f, DiffVector.Rotation().Yaw, 0.f);
	
	RotationState = FRotationState{ LookAtRotation, StopWhenFaceTarget };
}

void ABaseCharacter::EndRotating()
{
	bIsRotating = false;
	RotationState = FRotationState();
	OnRotationEnd.Broadcast();
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsRotating)
	{
		const FRotator NextRotation = FMath::RInterpConstantTo(GetActorRotation(), RotationState.Target, DeltaTime, 650.f);
		SetActorRotation(NextRotation);
		if (RotationState.bEndWhenFaceTarget && GetActorRotation().Equals(RotationState.Target, 0.001f))
		{
			EndRotating();
		}
	}
}
