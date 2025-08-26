
#include "BeamableCore/Public/AutoGen/RealmsBasicCustomerViewLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString URealmsBasicCustomerViewLibrary::RealmsBasicCustomerViewToJsonString(const URealmsBasicCustomerView* Serializable, const bool Pretty)
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

URealmsBasicCustomerView* URealmsBasicCustomerViewLibrary::Make(FBeamCid Cid, FString Name, TArray<UProjectView*> Projects, FOptionalString Alias, UObject* Outer)
{
	auto Serializable = NewObject<URealmsBasicCustomerView>(Outer);
	Serializable->Cid = Cid;
	Serializable->Name = Name;
	Serializable->Projects = Projects;
	Serializable->Alias = Alias;
	
	return Serializable;
}

void URealmsBasicCustomerViewLibrary::Break(const URealmsBasicCustomerView* Serializable, FBeamCid& Cid, FString& Name, TArray<UProjectView*>& Projects, FOptionalString& Alias)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Cid = Serializable->Cid;
		Name = Serializable->Name;
		Projects = Serializable->Projects;
		Alias = Serializable->Alias;
	}
		
}

