#pragma once

#include "CoreMinimal.h"
#include "Analytics/BeamAnalyticsEvent.h"

/**
 * Static validator helpers used by code-generated FBeamAnalyticsEvent subtypes
 * inside their Validate(FBeamValidationContext&) override. One function per JSON
 * Schema constraint, named after the schema keyword.
 *
 * Each function appends a human-readable error string to Result via AddError when
 * the constraint is violated; the per-property FBeamValidationResult is then
 * routed by FBeamValidationContext::RecordResult into Pass or Fail.
 */
namespace BeamValidators
{
	// ── Numeric (integer) ────────────────────────────────────────────────
	BEAMABLECORERUNTIME_API void ValidateMinimum         (int32 Value, int32 Minimum,         FBeamValidationResult& Result);
	BEAMABLECORERUNTIME_API void ValidateMaximum         (int32 Value, int32 Maximum,         FBeamValidationResult& Result);
	BEAMABLECORERUNTIME_API void ValidateExclusiveMinimum(int32 Value, int32 ExclusiveMinimum, FBeamValidationResult& Result);
	BEAMABLECORERUNTIME_API void ValidateExclusiveMaximum(int32 Value, int32 ExclusiveMaximum, FBeamValidationResult& Result);
	BEAMABLECORERUNTIME_API void ValidateMultipleOf      (int32 Value, int32 MultipleOf,      FBeamValidationResult& Result);

	// ── Numeric (float) ──────────────────────────────────────────────────
	BEAMABLECORERUNTIME_API void ValidateMinimum         (float Value, float Minimum,         FBeamValidationResult& Result);
	BEAMABLECORERUNTIME_API void ValidateMaximum         (float Value, float Maximum,         FBeamValidationResult& Result);
	BEAMABLECORERUNTIME_API void ValidateExclusiveMinimum(float Value, float ExclusiveMinimum, FBeamValidationResult& Result);
	BEAMABLECORERUNTIME_API void ValidateExclusiveMaximum(float Value, float ExclusiveMaximum, FBeamValidationResult& Result);
	BEAMABLECORERUNTIME_API void ValidateMultipleOf      (float Value, float MultipleOf,      FBeamValidationResult& Result);

	// ── String ───────────────────────────────────────────────────────────
	BEAMABLECORERUNTIME_API void ValidateMinLength(const FString& Value, int32 MinLength, FBeamValidationResult& Result);
	BEAMABLECORERUNTIME_API void ValidateMaxLength(const FString& Value, int32 MaxLength, FBeamValidationResult& Result);
	BEAMABLECORERUNTIME_API void ValidatePattern  (const FString& Value, const FString& Pattern, FBeamValidationResult& Result);
	BEAMABLECORERUNTIME_API void ValidateRequired (const FString& Value, FBeamValidationResult& Result);
}
