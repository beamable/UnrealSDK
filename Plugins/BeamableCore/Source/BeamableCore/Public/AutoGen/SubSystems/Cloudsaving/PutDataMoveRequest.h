
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/PlayerBasicCloudDataRequestBody.h"
#include "BeamableCore/Public/AutoGen/CloudsavingBasicManifest.h"

#include "PutDataMoveRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutDataMoveRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UPlayerBasicCloudDataRequestBody* Body = {};

	// Beam Base Request Declaration
	UPutDataMoveRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Cloudsaving|Utils|Make/Break", DisplayName="Make PutDataMove",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_PlayerId,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPutDataMoveRequest* Make(FOptionalInt64 _PlayerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutDataMoveSuccess, FBeamRequestContext, Context, UPutDataMoveRequest*, Request, UCloudsavingBasicManifest*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutDataMoveError, FBeamRequestContext, Context, UPutDataMoveRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutDataMoveComplete, FBeamRequestContext, Context, UPutDataMoveRequest*, Request);

using FPutDataMoveFullResponse = FBeamFullResponse<UPutDataMoveRequest*, UCloudsavingBasicManifest*>;
DECLARE_DELEGATE_OneParam(FOnPutDataMoveFullResponse, FPutDataMoveFullResponse);
