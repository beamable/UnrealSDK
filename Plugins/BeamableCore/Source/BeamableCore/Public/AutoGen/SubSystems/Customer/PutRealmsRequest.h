
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/EmptyMessage.h"

#include "PutRealmsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutRealmsRequest : public UObject, public IBeamBaseRequestInterface
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
	UPutRealmsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Customer|Utils|Make/Break", DisplayName="Make PutRealms",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPutRealmsRequest* Make(FString _CustomerId, FString _RealmId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutRealmsSuccess, FBeamRequestContext, Context, UPutRealmsRequest*, Request, UEmptyMessage*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutRealmsError, FBeamRequestContext, Context, UPutRealmsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutRealmsComplete, FBeamRequestContext, Context, UPutRealmsRequest*, Request);

using FPutRealmsFullResponse = FBeamFullResponse<UPutRealmsRequest*, UEmptyMessage*>;
DECLARE_DELEGATE_OneParam(FOnPutRealmsFullResponse, FPutRealmsFullResponse);
