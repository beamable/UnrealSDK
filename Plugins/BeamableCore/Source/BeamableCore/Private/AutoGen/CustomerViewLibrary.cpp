
#include "BeamableCore/Public/AutoGen/CustomerViewLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCustomerViewLibrary::CustomerViewToJsonString(const UCustomerView* Serializable, const bool Pretty)
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

UCustomerView* UCustomerViewLibrary::Make(FBeamCid Cid, FString Name, TArray<UProjectView*> Projects, FOptionalString Alias, UObject* Outer)
{
	auto Serializable = NewObject<UCustomerView>(Outer);
	Serializable->Cid = Cid;
	Serializable->Name = Name;
	Serializable->Projects = Projects;
	Serializable->Alias = Alias;
	
	return Serializable;
}

void UCustomerViewLibrary::Break(const UCustomerView* Serializable, FBeamCid& Cid, FString& Name, TArray<UProjectView*>& Projects, FOptionalString& Alias)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Cid = Serializable->Cid;
		Name = Serializable->Name;
		Projects = Serializable->Projects;
		Alias = Serializable->Alias;
	}
		
}

