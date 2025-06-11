
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/GetServiceURLsRequestBody.h"
#include "BeamableCore/Public/AutoGen/PreSignedUrlsResponse.h"

#include "PostImageUrlsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostImageUrlsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UGetServiceURLsRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostImageUrlsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make PostImageUrls",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostImageUrlsRequest* Make(TArray<UServiceImageLayers*> _Requests, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostImageUrlsSuccess, FBeamRequestContext, Context, UPostImageUrlsRequest*, Request, UPreSignedUrlsResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostImageUrlsError, FBeamRequestContext, Context, UPostImageUrlsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostImageUrlsComplete, FBeamRequestContext, Context, UPostImageUrlsRequest*, Request);

using FPostImageUrlsFullResponse = FBeamFullResponse<UPostImageUrlsRequest*, UPreSignedUrlsResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostImageUrlsFullResponse, FPostImageUrlsFullResponse);
