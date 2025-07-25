
#include "BeamableCore/Public/AutoGen/RoleMappingLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString URoleMappingLibrary::RoleMappingToJsonString(const URoleMapping* Serializable, const bool Pretty)
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

URoleMapping* URoleMappingLibrary::Make(FString ProjectId, FString Role, UObject* Outer)
{
	auto Serializable = NewObject<URoleMapping>(Outer);
	Serializable->ProjectId = ProjectId;
	Serializable->Role = Role;
	
	return Serializable;
}

void URoleMappingLibrary::Break(const URoleMapping* Serializable, FString& ProjectId, FString& Role)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ProjectId = Serializable->ProjectId;
		Role = Serializable->Role;
	}
		
}

