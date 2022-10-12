
#include "DeleteMeDeviceRequest.h"

void UDeleteMeDeviceRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("DELETE");
}

void UDeleteMeDeviceRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/accounts/me/device");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UDeleteMeDeviceRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UDeleteMeDeviceRequest* UDeleteMeDeviceRequest::MakeDeleteMeDeviceRequest(FOptionalArrayOfString _DeviceIds, UObject* Outer)
{
	UDeleteMeDeviceRequest* Req = NewObject<UDeleteMeDeviceRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UDeleteDevicesRequestBody>(Req);
	Req->Body->DeviceIds = _DeviceIds;
	

	return Req;
}
