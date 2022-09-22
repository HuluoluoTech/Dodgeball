// Fill out your copyright notice in the Description page of Project Settings.


#include "EnamyCharacter.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DodgeballFunctionLibrary.h"

// Sets default values
AEnamyCharacter::AEnamyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SightSource = CreateDefaultSubobject<USceneComponent>(TEXT("EnemyCharacter"));
	SightSource->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AEnamyCharacter::BeginPlay()
{
	Super::BeginPlay();
	

}

// Called every frame
void AEnamyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	bCanSeePlayer = LookAtActor(PlayerCharacter);
	/*UE_LOG(LogTemp, Warning, TEXT("bCanSeePlayer = %d"), bCanSeePlayer);
	UE_LOG(LogTemp, Warning, TEXT("bPreviousCanSeePlayer = %d"), bPreviousCanSeePlayer);*/

	if (bCanSeePlayer != bPreviousCanSeePlayer) {
		if (bCanSeePlayer) {
			//UE_LOG(LogTemp, Warning, TEXT("bCanSeePlayer == true ,¿ªÆôTimer..."));

			//Start throwing dodgeballs
			GetWorldTimerManager().SetTimer(ThrowTimerHandle,
				this,
				&AEnamyCharacter::ThrowDodgeball,
				ThrowingInterval,
				true,
				ThrowingDelay);
		}
		else {
			//Stop throwing dodgeballs
			GetWorldTimerManager().ClearTimer(ThrowTimerHandle);
		}
	}
	bPreviousCanSeePlayer = bCanSeePlayer;
}

// Called to bind functionality to input
void AEnamyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool AEnamyCharacter::LookAtActor(const AActor* TargetActor)
{
	if (TargetActor == nullptr) return false;

	//bool CanSee = CanSeeActor(TargetActor);
	//UE_LOG(LogTemp, Warning, TEXT("CanSeeActor = %d"),CanSee);

	//if (CanSee)
	//{
	//	FVector CurrentActorLoction = GetActorLocation();
	//	FVector TargetActorLocation = TargetActor->GetActorLocation();
	//	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(CurrentActorLoction, TargetActorLocation);

	//	SetActorRotation(LookAtRotation);

	//	return true;
	//}

	//return false;


	const TArray<const AActor*> IgnoreActors = { this, TargetActor };
	if (UDodgeballFunctionLibrary::CanSeeActor(GetWorld(),
		SightSource->GetComponentLocation(),
		TargetActor,
		IgnoreActors))
	{
		FVector Start = GetActorLocation();
		FVector End = TargetActor->GetActorLocation();
		// Calculate the necessary rotation for the Start point to face the End point
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(Start, End);

		//Set the enemy's rotation to that rotation
		SetActorRotation(LookAtRotation);
		return true;
	}

	return false;
}
//
//bool AEnamyCharacter::CanSeeActor(const AActor* TargetActor) const
//{
//	if (TargetActor == nullptr) return false;
//
//	FHitResult Hit;
//	FVector CurrentActorLocation = SightSource->GetComponentLocation();
//	FVector TargetActorLocation = TargetActor->GetActorLocation();
//
//	FQuat Rotation = FQuat::Identity;
//	
//	 //ECollisionChannel CollisionChannel = ECollisionChannel::ECC_Visibility;
//	ECollisionChannel CollisionChannel = ECollisionChannel::ECC_GameTraceChannel1;
//	/*FCollisionShape Shape = FCollisionShape::MakeBox(FVector(20.0f, 20.0f, 20.0f));
//	GetWorld()->SweepSingleByChannel(Hit, CurrentActorLocation, TargetActorLocation, Rotation, CollisionChannel, Shape);*/
//
//	FCollisionQueryParams QueryParams;
//	QueryParams.AddIgnoredActor(this);
//	QueryParams.AddIgnoredActor(TargetActor);
//	GetWorld()->LineTraceSingleByChannel(Hit, CurrentActorLocation, TargetActorLocation, CollisionChannel, QueryParams);
//
//	// Show Debug
//	DrawDebugLine(GetWorld(), CurrentActorLocation, TargetActorLocation, FColor::Red);
//
//	/*
//	Hit.GetActor();
//	Hit.GetComponent();
//	Hit.Location;
//	Hit.Distance
//	*/;
//
//	return !Hit.bBlockingHit;
//}

void AEnamyCharacter::ThrowDodgeball()
{
	//UE_LOG(LogTemp, Warning, TEXT("THROW BALL...."));
	if (DodgeballClass == nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("THROW BALL nullptr"));
		return;
	}

	FVector ForwardVector = GetActorForwardVector();
	float SpawnDistance = 40.f;
	FVector SpawnLocation = GetActorLocation() + (ForwardVector * SpawnDistance);
	FTransform SpawnTransform(GetActorRotation(), SpawnLocation);

	//Spawn new dodgeball
	//GetWorld()->SpawnActor<ADodgeballProjectile>(DodgeballClass, SpawnLocation, GetActorRotation());
	ADodgeballProjectile* Projectile = GetWorld()->SpawnActorDeferred<ADodgeballProjectile>(DodgeballClass, SpawnTransform);

	Projectile->GetProjectileMovementComponent()->InitialSpeed = 2200.f;
	Projectile->FinishSpawning(SpawnTransform);
}
