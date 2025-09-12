
#include "BeamableCore/Public/AutoGen/PredicateDTOLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPredicateDTOLibrary::PredicateDTOToJsonString(const UPredicateDTO* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UPredicateDTO* UPredicateDTOLibrary::Make(FString Kind, FOptionalString As, FOptionalBool bCaseInsensitive, FOptionalBool bIncludeLower, FOptionalBool bIncludeUpper, FOptionalString Lower, FOptionalString Upper, FOptionalString Substr, FOptionalString Value, FOptionalArrayOfString Values, UObject* Outer)
{
	auto Serializable = NewObject<UPredicateDTO>(Outer);
	Serializable->Kind = Kind;
	Serializable->As = As;
	Serializable->bCaseInsensitive = bCaseInsensitive;
	Serializable->bIncludeLower = bIncludeLower;
	Serializable->bIncludeUpper = bIncludeUpper;
	Serializable->Lower = Lower;
	Serializable->Upper = Upper;
	Serializable->Substr = Substr;
	Serializable->Value = Value;
	Serializable->Values = Values;
	
	return Serializable;
}

void UPredicateDTOLibrary::Break(const UPredicateDTO* Serializable, FString& Kind, FOptionalString& As, FOptionalBool& bCaseInsensitive, FOptionalBool& bIncludeLower, FOptionalBool& bIncludeUpper, FOptionalString& Lower, FOptionalString& Upper, FOptionalString& Substr, FOptionalString& Value, FOptionalArrayOfString& Values)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Kind = Serializable->Kind;
		As = Serializable->As;
		bCaseInsensitive = Serializable->bCaseInsensitive;
		bIncludeLower = Serializable->bIncludeLower;
		bIncludeUpper = Serializable->bIncludeUpper;
		Lower = Serializable->Lower;
		Upper = Serializable->Upper;
		Substr = Serializable->Substr;
		Value = Serializable->Value;
		Values = Serializable->Values;
	}
		
}

