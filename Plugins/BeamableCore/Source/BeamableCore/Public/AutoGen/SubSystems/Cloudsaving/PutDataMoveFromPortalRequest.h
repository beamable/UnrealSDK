
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/PlayerBasicCloudDataRequestBody.h"
#include "BeamableCore/Public/AutoGen/CloudsavingBasicManifest.h"

#include "PutDataMoveFromPortalRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutDataMoveFromPortalRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UPlayerBasicCloudDataRequestBody* Body = {};

	// Beam Base Request Declaration
	UPutDataMoveFromPortalRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Cloudsaving|Utils|Make/Break", DisplayName="Make PutDataMoveFromPortal",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_PlayerId,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPutDataMoveFromPortalRequest* Make(FOptionalInt64 _PlayerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutDataMoveFromPortalSuccess, FBeamRequestContext, Context, UPutDataMoveFromPortalRequest*, Request, UCloudsavingBasicManifest*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutDataMoveFromPortalError, FBeamRequestContext, Context, UPutDataMoveFromPortalRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutDataMoveFromPortalComplete, FBeamRequestContext, Context, UPutDataMoveFromPortalRequest*, Request);

using FPutDataMoveFromPortalFullResponse = FBeamFullResponse<UPutDataMoveFromPortalRequest*, UCloudsavingBasicManifest*>;
DECLARE_DELEGATE_OneParam(FOnPutDataMoveFromPortalFullResponse, FPutDataMoveFromPortalFullResponse);
