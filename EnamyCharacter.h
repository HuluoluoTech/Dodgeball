// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TimerManager.h"
#include "DodgeballProjectile.h"
#include "EnamyCharacter.generated.h"

UCLASS()
class HULUOLUO_API AEnamyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnamyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	bool LookAtActor(const AActor* TargetActor);
	//bool CanSeeActor(const AActor* TargetActor) const;
	void ThrowDodgeball();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = LookAt, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* SightSource;

protected:
	bool bCanSeePlayer{ false };
	bool bPreviousCanSeePlayer{ false };
	FTimerHandle ThrowTimerHandle;

	float ThrowingInterval = 2.f;
	float ThrowingDelay = 0.5f;

	//The class used to spawn a dodgeball object
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Dodgeball)
		TSubclassOf<class ADodgeballProjectile> DodgeballClass;
};
