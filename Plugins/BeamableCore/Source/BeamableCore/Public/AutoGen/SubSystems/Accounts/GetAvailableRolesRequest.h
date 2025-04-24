
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamBackend/SemanticTypes/BeamAccountId.h"
#include "BeamableCore/Public/AutoGen/AvailableRolesResponse.h"

#include "GetAvailableRolesRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetAvailableRolesRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	FBeamAccountId ObjectId = {};
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetAvailableRolesRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Make GetAvailableRoles",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetAvailableRolesRequest* Make(FBeamAccountId _ObjectId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetAvailableRolesSuccess, FBeamRequestContext, Context, UGetAvailableRolesRequest*, Request, UAvailableRolesResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetAvailableRolesError, FBeamRequestContext, Context, UGetAvailableRolesRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetAvailableRolesComplete, FBeamRequestContext, Context, UGetAvailableRolesRequest*, Request);

using FGetAvailableRolesFullResponse = FBeamFullResponse<UGetAvailableRolesRequest*, UAvailableRolesResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetAvailableRolesFullResponse, FGetAvailableRolesFullResponse);
