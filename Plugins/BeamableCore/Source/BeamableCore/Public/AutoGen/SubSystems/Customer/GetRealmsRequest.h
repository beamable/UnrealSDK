
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/RealmView.h"

#include "GetRealmsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetRealmsRequest : public UObject, public IBeamBaseRequestInterface
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
	UGetRealmsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Customer|Utils|Make/Break", DisplayName="Make GetRealms",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetRealmsRequest* Make(FString _CustomerId, FString _RealmId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetRealmsSuccess, FBeamRequestContext, Context, UGetRealmsRequest*, Request, URealmView*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetRealmsError, FBeamRequestContext, Context, UGetRealmsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetRealmsComplete, FBeamRequestContext, Context, UGetRealmsRequest*, Request);

using FGetRealmsFullResponse = FBeamFullResponse<UGetRealmsRequest*, URealmView*>;
DECLARE_DELEGATE_OneParam(FOnGetRealmsFullResponse, FGetRealmsFullResponse);
