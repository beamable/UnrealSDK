
#include "BeamableCore/Public/AutoGen/SubSystems/Content/GetManifestDiffsRequest.h"

void UGetManifestDiffsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetManifestDiffsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/content/manifest/diffs");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), TEXT("manifestId"), *static_cast<FString>(ManifestId));
	bIsFirstQueryParam = false;
	
	if(FromUid.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("fromUid"), *FromUid.Val);
		bIsFirstQueryParam = false;
	}

	if(ToUid.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("toUid"), *ToUid.Val);
		bIsFirstQueryParam = false;
	}

	if(Offset.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("offset"), *FString::FromInt(Offset.Val));
		bIsFirstQueryParam = false;
	}

	if(Limit.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("limit"), *FString::FromInt(Limit.Val));
		bIsFirstQueryParam = false;
	}

	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetManifestDiffsRequest::BuildBody(FString& BodyString) const
{
	
}

UGetManifestDiffsRequest* UGetManifestDiffsRequest::Make(FBeamContentManifestId _ManifestId, FOptionalString _FromUid, FOptionalString _ToUid, FOptionalInt32 _Offset, FOptionalInt32 _Limit, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetManifestDiffsRequest* Req = NewObject<UGetManifestDiffsRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ManifestId = _ManifestId;
	Req->FromUid = _FromUid;
	Req->ToUid = _ToUid;
	Req->Offset = _Offset;
	Req->Limit = _Limit;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
