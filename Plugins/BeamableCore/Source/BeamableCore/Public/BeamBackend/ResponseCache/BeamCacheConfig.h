// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"

#include "BeamCacheConfig.generated.h"

UENUM(BlueprintType)
enum EBeamCacheMode
{
	/**
	 * @brief When in this mode, request responses are not cached. This is the default.
	 */
	Disabled = 0,

	/**
	 * @brief When in this mode, request responses are cached and then invalidated after X amount of time has passed. 
	 */
	Time,

	/**
	 * @brief When in this mode, request responses are cached and then invalidated if the configured conditional is true (check one use, if a certain amount of time has passed).
	 */
	ConditionalOnTime,
};

DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(bool, FShouldInvalidateCache, const TScriptInterface<IBeamBaseRequestInterface>, RequestData);

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamCacheConfig
{
	GENERATED_BODY()

	/**
	 * @brief The Mode of this cache configuration.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Beam")
	TEnumAsByte<EBeamCacheMode> Mode = EBeamCacheMode::Disabled;

	/**
	 * @brief The amount of time in seconds in which the cache will be invalidated (or checked for invalidation when in ConditionalOnTime mode).
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Beam")
	double Time = 0.0;

	/**
	 * @brief The delegate to run to check for invalidation (only relevant if in ConditionalOnTime mode).
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Beam")
	FShouldInvalidateCache ShouldInvalidateCacheDelegate;
};
