
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "AutoGen/ObjectRequests.h"
#include "AutoGen/URLSResponse.h"

#include "PostDataDownloadURLRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostDataDownloadURLRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UObjectRequests* Body;

	// Beam Base Request Declaration
	UPostDataDownloadURLRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Cloudsaving", DisplayName="Beam - Make PostDataDownloadURL",  meta=(DefaultToSelf="Outer", AdvancedDisplay="_PlayerId,_Request,Outer"))
	static UPostDataDownloadURLRequest* Make(FOptionalInt64 _PlayerId, FOptionalArrayOfObjectRequestBody _Request, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostDataDownloadURLSuccess, FBeamRequestContext, Context, UPostDataDownloadURLRequest*, Request, UURLSResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostDataDownloadURLError, FBeamRequestContext, Context, UPostDataDownloadURLRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostDataDownloadURLComplete, FBeamRequestContext, Context, UPostDataDownloadURLRequest*, Request);

using FPostDataDownloadURLFullResponse = FBeamFullResponse<UPostDataDownloadURLRequest*, UURLSResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostDataDownloadURLFullResponse, FPostDataDownloadURLFullResponse);
