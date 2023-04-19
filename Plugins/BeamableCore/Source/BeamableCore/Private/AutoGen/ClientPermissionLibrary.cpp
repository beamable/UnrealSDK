
#include "BeamableCore/Public/AutoGen/ClientPermissionLibrary.h"

#include "CoreMinimal.h"


FString UClientPermissionLibrary::ClientPermissionToJsonString(const UClientPermission* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UClientPermission* UClientPermissionLibrary::Make(bool bWriteSelf, UObject* Outer)
{
	auto Serializable = NewObject<UClientPermission>(Outer);
	Serializable->bWriteSelf = bWriteSelf;
	
	return Serializable;
}

void UClientPermissionLibrary::Break(const UClientPermission* Serializable, bool& bWriteSelf)
{
	bWriteSelf = Serializable->bWriteSelf;
		
}

