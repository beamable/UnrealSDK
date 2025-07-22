
#include "BeamableCore/Public/AutoGen/GetCurrentManifestRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetCurrentManifestRequestBodyLibrary::GetCurrentManifestRequestBodyToJsonString(const UGetCurrentManifestRequestBody* Serializable, const bool Pretty)
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

UGetCurrentManifestRequestBody* UGetCurrentManifestRequestBodyLibrary::Make(FOptionalBool bArchived, UObject* Outer)
{
	auto Serializable = NewObject<UGetCurrentManifestRequestBody>(Outer);
	Serializable->bArchived = bArchived;
	
	return Serializable;
}

void UGetCurrentManifestRequestBodyLibrary::Break(const UGetCurrentManifestRequestBody* Serializable, FOptionalBool& bArchived)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bArchived = Serializable->bArchived;
	}
		
}

