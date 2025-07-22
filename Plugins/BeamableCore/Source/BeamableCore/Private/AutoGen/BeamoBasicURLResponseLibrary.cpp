
#include "BeamableCore/Public/AutoGen/BeamoBasicURLResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoBasicURLResponseLibrary::BeamoBasicURLResponseToJsonString(const UBeamoBasicURLResponse* Serializable, const bool Pretty)
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

UBeamoBasicURLResponse* UBeamoBasicURLResponseLibrary::Make(FString ServiceName, TArray<UUploadURL*> S3URLs, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoBasicURLResponse>(Outer);
	Serializable->ServiceName = ServiceName;
	Serializable->S3URLs = S3URLs;
	
	return Serializable;
}

void UBeamoBasicURLResponseLibrary::Break(const UBeamoBasicURLResponse* Serializable, FString& ServiceName, TArray<UUploadURL*>& S3URLs)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ServiceName = Serializable->ServiceName;
		S3URLs = Serializable->S3URLs;
	}
		
}

