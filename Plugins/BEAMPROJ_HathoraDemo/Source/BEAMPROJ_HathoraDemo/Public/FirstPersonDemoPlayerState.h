// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Net/UnrealNetwork.h"
#include "FirstPersonDemoPlayerState.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class BEAMPROJ_HATHORADEMO_API AFirstPersonDemoPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Replicated)
	FString BeamableGamerTag;

	UPROPERTY(BlueprintReadWrite, Replicated)
	float PlayerHP;

	virtual void BeginPlay() override
	{
		SetNetUpdateFrequency(30);
	}
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override
	{		
		Super::GetLifetimeReplicatedProps(OutLifetimeProps);
		DOREPLIFETIME(AFirstPersonDemoPlayerState, BeamableGamerTag);
		DOREPLIFETIME(AFirstPersonDemoPlayerState, PlayerHP);		
	}

	
	UFUNCTION(BlueprintCallable, Server, Reliable)
	void TakeDamageFromProjectile(float Damage);
	void TakeDamageFromProjectile_Implementation(float Damage)
	{
		PlayerHP -= Damage;
		PlayerHP = FMath::CeilToFloat(PlayerHP);
	}
};
