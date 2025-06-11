
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/UploadRequestsFromPortal.h"
#include "BeamableCore/Public/AutoGen/URLSResponse.h"

#include "PostDataUploadURLFromPortalRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostDataUploadURLFromPortalRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UUploadRequestsFromPortal* Body = {};

	// Beam Base Request Declaration
	UPostDataUploadURLFromPortalRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Cloudsaving|Utils|Make/Break", DisplayName="Make PostDataUploadURLFromPortal",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_PlayerId,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostDataUploadURLFromPortalRequest* Make(TArray<UUploadRequestFromPortal*> _Request, FOptionalInt64 _PlayerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostDataUploadURLFromPortalSuccess, FBeamRequestContext, Context, UPostDataUploadURLFromPortalRequest*, Request, UURLSResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostDataUploadURLFromPortalError, FBeamRequestContext, Context, UPostDataUploadURLFromPortalRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostDataUploadURLFromPortalComplete, FBeamRequestContext, Context, UPostDataUploadURLFromPortalRequest*, Request);

using FPostDataUploadURLFromPortalFullResponse = FBeamFullResponse<UPostDataUploadURLFromPortalRequest*, UURLSResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostDataUploadURLFromPortalFullResponse, FPostDataUploadURLFromPortalFullResponse);
