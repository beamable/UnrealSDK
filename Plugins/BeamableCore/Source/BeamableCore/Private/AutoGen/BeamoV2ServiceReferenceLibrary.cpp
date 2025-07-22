
#include "BeamableCore/Public/AutoGen/BeamoV2ServiceReferenceLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoV2ServiceReferenceLibrary::BeamoV2ServiceReferenceToJsonString(const UBeamoV2ServiceReference* Serializable, const bool Pretty)
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

UBeamoV2ServiceReference* UBeamoV2ServiceReferenceLibrary::Make(FOptionalBool bArchived, FOptionalBool bEnabled, FOptionalString ServiceName, FOptionalString ImageId, FOptionalString TemplateId, FOptionalString Comments, FOptionalInt32 ContainerHealthCheckPort, FOptionalString ImageCpuArch, FOptionalString Checksum, FOptionalArrayOfBeamoV2ServiceDependencyReference Dependencies, FOptionalArrayOfBeamoV2ServiceComponent Components, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoV2ServiceReference>(Outer);
	Serializable->bArchived = bArchived;
	Serializable->bEnabled = bEnabled;
	Serializable->ServiceName = ServiceName;
	Serializable->ImageId = ImageId;
	Serializable->TemplateId = TemplateId;
	Serializable->Comments = Comments;
	Serializable->ContainerHealthCheckPort = ContainerHealthCheckPort;
	Serializable->ImageCpuArch = ImageCpuArch;
	Serializable->Checksum = Checksum;
	Serializable->Dependencies = Dependencies;
	Serializable->Components = Components;
	
	return Serializable;
}

void UBeamoV2ServiceReferenceLibrary::Break(const UBeamoV2ServiceReference* Serializable, FOptionalBool& bArchived, FOptionalBool& bEnabled, FOptionalString& ServiceName, FOptionalString& ImageId, FOptionalString& TemplateId, FOptionalString& Comments, FOptionalInt32& ContainerHealthCheckPort, FOptionalString& ImageCpuArch, FOptionalString& Checksum, FOptionalArrayOfBeamoV2ServiceDependencyReference& Dependencies, FOptionalArrayOfBeamoV2ServiceComponent& Components)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bArchived = Serializable->bArchived;
		bEnabled = Serializable->bEnabled;
		ServiceName = Serializable->ServiceName;
		ImageId = Serializable->ImageId;
		TemplateId = Serializable->TemplateId;
		Comments = Serializable->Comments;
		ContainerHealthCheckPort = Serializable->ContainerHealthCheckPort;
		ImageCpuArch = Serializable->ImageCpuArch;
		Checksum = Serializable->Checksum;
		Dependencies = Serializable->Dependencies;
		Components = Serializable->Components;
	}
		
}

