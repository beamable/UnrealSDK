#include "Runtime/BeamValidators.h"

#include "Internationalization/Regex.h"
#include "Math/UnrealMathUtility.h"

// ── Numeric (integer) ────────────────────────────────────────────────────────

void UBeamValidators::ValidateMinimum(int32 Value, int32 Minimum, FBeamValidationResult& Result)
{
	if (Value < Minimum)
	{
		Result.AddError(
			FString::Printf(TEXT("Value %d is less than minimum %d"), Value, Minimum),
			TEXT("MINIMUM_VIOLATION"));
	}
}

void UBeamValidators::ValidateMaximum(int32 Value, int32 Maximum, FBeamValidationResult& Result)
{
	if (Value > Maximum)
	{
		Result.AddError(
			FString::Printf(TEXT("Value %d is greater than maximum %d"), Value, Maximum),
			TEXT("MAXIMUM_VIOLATION"));
	}
}

void UBeamValidators::ValidateExclusiveMinimum(int32 Value, int32 ExclusiveMinimum, FBeamValidationResult& Result)
{
	if (Value <= ExclusiveMinimum)
	{
		Result.AddError(
			FString::Printf(TEXT("Value %d must be greater than %d"), Value, ExclusiveMinimum),
			TEXT("EXCLUSIVE_MINIMUM_VIOLATION"));
	}
}

void UBeamValidators::ValidateExclusiveMaximum(int32 Value, int32 ExclusiveMaximum, FBeamValidationResult& Result)
{
	if (Value >= ExclusiveMaximum)
	{
		Result.AddError(
			FString::Printf(TEXT("Value %d must be less than %d"), Value, ExclusiveMaximum),
			TEXT("EXCLUSIVE_MAXIMUM_VIOLATION"));
	}
}

void UBeamValidators::ValidateMultipleOf(int32 Value, int32 MultipleOf, FBeamValidationResult& Result)
{
	if (MultipleOf != 0 && Value % MultipleOf != 0)
	{
		Result.AddError(
			FString::Printf(TEXT("Value %d is not a multiple of %d"), Value, MultipleOf),
			TEXT("MULTIPLE_OF_VIOLATION"));
	}
}

// ── Numeric (float) ──────────────────────────────────────────────────────────

void UBeamValidators::ValidateMinimum(float Value, float Minimum, FBeamValidationResult& Result)
{
	if (Value < Minimum)
	{
		Result.AddError(
			FString::Printf(TEXT("Value %f is less than minimum %f"), Value, Minimum),
			TEXT("MINIMUM_VIOLATION"));
	}
}

void UBeamValidators::ValidateMaximum(float Value, float Maximum, FBeamValidationResult& Result)
{
	if (Value > Maximum)
	{
		Result.AddError(
			FString::Printf(TEXT("Value %f is greater than maximum %f"), Value, Maximum),
			TEXT("MAXIMUM_VIOLATION"));
	}
}

void UBeamValidators::ValidateExclusiveMinimum(float Value, float ExclusiveMinimum, FBeamValidationResult& Result)
{
	if (Value <= ExclusiveMinimum)
	{
		Result.AddError(
			FString::Printf(TEXT("Value %f must be greater than %f"), Value, ExclusiveMinimum),
			TEXT("EXCLUSIVE_MINIMUM_VIOLATION"));
	}
}

void UBeamValidators::ValidateExclusiveMaximum(float Value, float ExclusiveMaximum, FBeamValidationResult& Result)
{
	if (Value >= ExclusiveMaximum)
	{
		Result.AddError(
			FString::Printf(TEXT("Value %f must be less than %f"), Value, ExclusiveMaximum),
			TEXT("EXCLUSIVE_MAXIMUM_VIOLATION"));
	}
}

void UBeamValidators::ValidateMultipleOf(float Value, float MultipleOf, FBeamValidationResult& Result)
{
	if (MultipleOf != 0.0f)
	{
		const float Mod = FMath::Fmod(Value, MultipleOf);
		if (FMath::Abs(Mod) > KINDA_SMALL_NUMBER)
		{
			Result.AddError(
				FString::Printf(TEXT("Value %f is not a multiple of %f"), Value, MultipleOf),
				TEXT("MULTIPLE_OF_VIOLATION"));
		}
	}
}

// ── String ───────────────────────────────────────────────────────────────────

void UBeamValidators::ValidateMinLength(const FString& Value, int32 MinLength, FBeamValidationResult& Result)
{
	if (Value.Len() < MinLength)
	{
		Result.AddError(
			FString::Printf(TEXT("String length %d is less than minimum length %d"), Value.Len(), MinLength),
			TEXT("MIN_LENGTH_VIOLATION"));
	}
}

void UBeamValidators::ValidateMaxLength(const FString& Value, int32 MaxLength, FBeamValidationResult& Result)
{
	if (Value.Len() > MaxLength)
	{
		Result.AddError(
			FString::Printf(TEXT("String length %d is greater than maximum length %d"), Value.Len(), MaxLength),
			TEXT("MAX_LENGTH_VIOLATION"));
	}
}

void UBeamValidators::ValidatePattern(const FString& Value, const FString& Pattern, FBeamValidationResult& Result)
{
	const FRegexPattern RegexPattern(Pattern);
	FRegexMatcher Matcher(RegexPattern, Value);
	if (!Matcher.FindNext())
	{
		Result.AddError(
			FString::Printf(TEXT("String does not match pattern: %s"), *Pattern),
			TEXT("PATTERN_VIOLATION"));
	}
}

void UBeamValidators::ValidateRequired(const FString& Value, FBeamValidationResult& Result)
{
	if (Value.IsEmpty())
	{
		Result.AddError(TEXT("Required field is empty"), TEXT("REQUIRED_VIOLATION"));
	}
}
