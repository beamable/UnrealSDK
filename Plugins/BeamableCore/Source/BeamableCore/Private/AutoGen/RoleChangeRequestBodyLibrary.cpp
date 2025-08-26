
#include "BeamableCore/Public/AutoGen/RoleChangeRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString URoleChangeRequestBodyLibrary::RoleChangeRequestBodyToJsonString(const URoleChangeRequestBody* Serializable, const bool Pretty)
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

URoleChangeRequestBody* URoleChangeRequestBodyLibrary::Make(int64 GamerTag, FString Role, FOptionalInt64 SubGroup, UObject* Outer)
{
	auto Serializable = NewObject<URoleChangeRequestBody>(Outer);
	Serializable->GamerTag = GamerTag;
	Serializable->Role = Role;
	Serializable->SubGroup = SubGroup;
	
	return Serializable;
}

void URoleChangeRequestBodyLibrary::Break(const URoleChangeRequestBody* Serializable, int64& GamerTag, FString& Role, FOptionalInt64& SubGroup)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		GamerTag = Serializable->GamerTag;
		Role = Serializable->Role;
		SubGroup = Serializable->SubGroup;
	}
		
}

