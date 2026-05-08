#pragma once

#include "CoreMinimal.h"
#include "Analytics/BeamAnalyticsEvent.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "BeamValidators.generated.h"

/**
 * Static validator library used by code-generated FBeamAnalyticsEvent subtypes
 * inside their Validate(FBeamValidationContext&) override. One method per JSON
 * Schema constraint, named after the schema keyword.
 *
 * Each method appends a human-readable error string to Result via AddError when
 * the constraint is violated; the per-property FBeamValidationResult is then
 * routed by FBeamValidationContext::RecordResult into Pass or Fail.
 */
UCLASS()
class BEAMABLECORERUNTIME_API UBeamValidators : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// ── Numeric (integer) ────────────────────────────────────────────────
	static void ValidateMinimum         (int32 Value, int32 Minimum,         FBeamValidationResult& Result);
	static void ValidateMaximum         (int32 Value, int32 Maximum,         FBeamValidationResult& Result);
	static void ValidateExclusiveMinimum(int32 Value, int32 ExclusiveMinimum, FBeamValidationResult& Result);
	static void ValidateExclusiveMaximum(int32 Value, int32 ExclusiveMaximum, FBeamValidationResult& Result);
	static void ValidateMultipleOf      (int32 Value, int32 MultipleOf,      FBeamValidationResult& Result);

	// ── Numeric (float) ──────────────────────────────────────────────────
	static void ValidateMinimum         (float Value, float Minimum,         FBeamValidationResult& Result);
	static void ValidateMaximum         (float Value, float Maximum,         FBeamValidationResult& Result);
	static void ValidateExclusiveMinimum(float Value, float ExclusiveMinimum, FBeamValidationResult& Result);
	static void ValidateExclusiveMaximum(float Value, float ExclusiveMaximum, FBeamValidationResult& Result);
	static void ValidateMultipleOf      (float Value, float MultipleOf,      FBeamValidationResult& Result);

	// ── String ───────────────────────────────────────────────────────────
	static void ValidateMinLength(const FString& Value, int32 MinLength, FBeamValidationResult& Result);
	static void ValidateMaxLength(const FString& Value, int32 MaxLength, FBeamValidationResult& Result);
	static void ValidatePattern  (const FString& Value, const FString& Pattern, FBeamValidationResult& Result);
	static void ValidateRequired (const FString& Value, FBeamValidationResult& Result);
};
