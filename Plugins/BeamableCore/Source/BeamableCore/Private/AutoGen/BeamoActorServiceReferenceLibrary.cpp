
#include "BeamableCore/Public/AutoGen/BeamoActorServiceReferenceLibrary.h"

#include "CoreMinimal.h"


FString UBeamoActorServiceReferenceLibrary::BeamoActorServiceReferenceToJsonString(const UBeamoActorServiceReference* Serializable, const bool Pretty)
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

UBeamoActorServiceReference* UBeamoActorServiceReferenceLibrary::Make(FOptionalBool bArchived, FOptionalBool bEnabled, FOptionalString ServiceName, FOptionalString ImageId, FOptionalString TemplateId, FOptionalString Comments, FOptionalInt32 ContainerHealthCheckPort, FOptionalString ImageCpuArch, FOptionalString Checksum, FOptionalArrayOfServiceDependencyReference Dependencies, FOptionalArrayOfServiceComponent Components, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoActorServiceReference>(Outer);
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

void UBeamoActorServiceReferenceLibrary::Break(const UBeamoActorServiceReference* Serializable, FOptionalBool& bArchived, FOptionalBool& bEnabled, FOptionalString& ServiceName, FOptionalString& ImageId, FOptionalString& TemplateId, FOptionalString& Comments, FOptionalInt32& ContainerHealthCheckPort, FOptionalString& ImageCpuArch, FOptionalString& Checksum, FOptionalArrayOfServiceDependencyReference& Dependencies, FOptionalArrayOfServiceComponent& Components)
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

