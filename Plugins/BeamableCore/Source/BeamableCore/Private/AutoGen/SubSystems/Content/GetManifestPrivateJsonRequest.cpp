
#include "BeamableCore/Public/AutoGen/SubSystems/Content/GetManifestPrivateJsonRequest.h"

void UGetManifestPrivateJsonRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetManifestPrivateJsonRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/content/manifest/private/json");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	if(Id.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("id"), *static_cast<FString>(Id.Val));
		bIsFirstQueryParam = false;
	}

	if(Uid.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("uid"), *Uid.Val);
		bIsFirstQueryParam = false;
	}

	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetManifestPrivateJsonRequest::BuildBody(FString& BodyString) const
{
	
}

UGetManifestPrivateJsonRequest* UGetManifestPrivateJsonRequest::Make(FOptionalBeamContentManifestId _Id, FOptionalString _Uid, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetManifestPrivateJsonRequest* Req = NewObject<UGetManifestPrivateJsonRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->Id = _Id;
	Req->Uid = _Uid;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
