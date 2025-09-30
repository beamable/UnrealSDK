
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/SetCustomerAliasRequestBody.h"
#include "BeamableCore/Public/AutoGen/EmptyMessage.h"

#include "PutAliasRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutAliasRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Customer Id", Category="Beam")
	FString CustomerId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	USetCustomerAliasRequestBody* Body = {};

	// Beam Base Request Declaration
	UPutAliasRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Customer|Utils|Make/Break", DisplayName="Make PutAlias",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPutAliasRequest* Make(FString _CustomerId, FString _Alias, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutAliasSuccess, FBeamRequestContext, Context, UPutAliasRequest*, Request, UEmptyMessage*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutAliasError, FBeamRequestContext, Context, UPutAliasRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutAliasComplete, FBeamRequestContext, Context, UPutAliasRequest*, Request);

using FPutAliasFullResponse = FBeamFullResponse<UPutAliasRequest*, UEmptyMessage*>;
DECLARE_DELEGATE_OneParam(FOnPutAliasFullResponse, FPutAliasFullResponse);
