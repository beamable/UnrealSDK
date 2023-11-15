
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/GetAvailableDeviceIdRequest.h"

void UGetAvailableDeviceIdRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetAvailableDeviceIdRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/accounts/available/device-id");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), TEXT("deviceId"), *DeviceId);
	bIsFirstQueryParam = false;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetAvailableDeviceIdRequest::BuildBody(FString& BodyString) const
{
	
}

UGetAvailableDeviceIdRequest* UGetAvailableDeviceIdRequest::Make(FString _DeviceId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetAvailableDeviceIdRequest* Req = NewObject<UGetAvailableDeviceIdRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->DeviceId = _DeviceId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
