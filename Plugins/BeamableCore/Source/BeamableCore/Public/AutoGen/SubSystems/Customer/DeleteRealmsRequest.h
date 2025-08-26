
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/EmptyMessage.h"

#include "DeleteRealmsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteRealmsRequest : public UObject, public IBeamBaseRequestInterface
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
	UDeleteRealmsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Customer|Utils|Make/Break", DisplayName="Make DeleteRealms",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UDeleteRealmsRequest* Make(FString _CustomerId, FString _RealmId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteRealmsSuccess, FBeamRequestContext, Context, UDeleteRealmsRequest*, Request, UEmptyMessage*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteRealmsError, FBeamRequestContext, Context, UDeleteRealmsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteRealmsComplete, FBeamRequestContext, Context, UDeleteRealmsRequest*, Request);

using FDeleteRealmsFullResponse = FBeamFullResponse<UDeleteRealmsRequest*, UEmptyMessage*>;
DECLARE_DELEGATE_OneParam(FOnDeleteRealmsFullResponse, FDeleteRealmsFullResponse);
