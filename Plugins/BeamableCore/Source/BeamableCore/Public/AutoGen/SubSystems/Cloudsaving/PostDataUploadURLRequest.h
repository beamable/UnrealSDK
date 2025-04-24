
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/UploadRequests.h"
#include "BeamableCore/Public/AutoGen/URLSResponse.h"

#include "PostDataUploadURLRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostDataUploadURLRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UUploadRequests* Body = {};

	// Beam Base Request Declaration
	UPostDataUploadURLRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Cloudsaving|Utils|Make/Break", DisplayName="Make PostDataUploadURL",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_PlayerId,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostDataUploadURLRequest* Make(TArray<UUploadRequestBody*> _Request, FOptionalInt64 _PlayerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostDataUploadURLSuccess, FBeamRequestContext, Context, UPostDataUploadURLRequest*, Request, UURLSResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostDataUploadURLError, FBeamRequestContext, Context, UPostDataUploadURLRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostDataUploadURLComplete, FBeamRequestContext, Context, UPostDataUploadURLRequest*, Request);

using FPostDataUploadURLFullResponse = FBeamFullResponse<UPostDataUploadURLRequest*, UURLSResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostDataUploadURLFullResponse, FPostDataUploadURLFullResponse);
