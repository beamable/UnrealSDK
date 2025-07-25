
#include "BeamableCore/Public/AutoGen/GetSkusReqLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetSkusReqLibrary::GetSkusReqToJsonString(const UGetSkusReq* Serializable, const bool Pretty)
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

UGetSkusReq* UGetSkusReqLibrary::Make(FOptionalInt64 Version, UObject* Outer)
{
	auto Serializable = NewObject<UGetSkusReq>(Outer);
	Serializable->Version = Version;
	
	return Serializable;
}

void UGetSkusReqLibrary::Break(const UGetSkusReq* Serializable, FOptionalInt64& Version)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Version = Serializable->Version;
	}
		
}

