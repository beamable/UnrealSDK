
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/RealmConfigSaveRequestBody.h"
#include "BeamableCore/Public/AutoGen/EmptyMessage.h"

#include "PutRealmsConfigRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutRealmsConfigRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Customer Id", Category="Beam")
	FString CustomerId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Realm Id", Category="Beam")
	FString RealmId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	URealmConfigSaveRequestBody* Body = {};

	// Beam Base Request Declaration
	UPutRealmsConfigRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Customer|Utils|Make/Break", DisplayName="Make PutRealmsConfig",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Config,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPutRealmsConfigRequest* Make(FString _CustomerId, FString _RealmId, FOptionalMapOfString _Config, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutRealmsConfigSuccess, FBeamRequestContext, Context, UPutRealmsConfigRequest*, Request, UEmptyMessage*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutRealmsConfigError, FBeamRequestContext, Context, UPutRealmsConfigRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutRealmsConfigComplete, FBeamRequestContext, Context, UPutRealmsConfigRequest*, Request);

using FPutRealmsConfigFullResponse = FBeamFullResponse<UPutRealmsConfigRequest*, UEmptyMessage*>;
DECLARE_DELEGATE_OneParam(FOnPutRealmsConfigFullResponse, FPutRealmsConfigFullResponse);
