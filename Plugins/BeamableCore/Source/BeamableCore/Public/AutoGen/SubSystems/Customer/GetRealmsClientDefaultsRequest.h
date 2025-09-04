
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/CustomerActorRealmConfiguration.h"

#include "GetRealmsClientDefaultsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetRealmsClientDefaultsRequest : public UObject, public IBeamBaseRequestInterface
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
	

	// Beam Base Request Declaration
	UGetRealmsClientDefaultsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Customer|Utils|Make/Break", DisplayName="Make GetRealmsClientDefaults",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetRealmsClientDefaultsRequest* Make(FString _CustomerId, FString _RealmId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetRealmsClientDefaultsSuccess, FBeamRequestContext, Context, UGetRealmsClientDefaultsRequest*, Request, UCustomerActorRealmConfiguration*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetRealmsClientDefaultsError, FBeamRequestContext, Context, UGetRealmsClientDefaultsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetRealmsClientDefaultsComplete, FBeamRequestContext, Context, UGetRealmsClientDefaultsRequest*, Request);

using FGetRealmsClientDefaultsFullResponse = FBeamFullResponse<UGetRealmsClientDefaultsRequest*, UCustomerActorRealmConfiguration*>;
DECLARE_DELEGATE_OneParam(FOnGetRealmsClientDefaultsFullResponse, FGetRealmsClientDefaultsFullResponse);
