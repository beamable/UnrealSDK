
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/AvailableRolesResponse.h"

#include "GetAvailableRolesRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetAvailableRolesRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetAvailableRolesRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UGetAvailableRolesRequest* MakeGetAvailableRolesRequest(int64 _ObjectId, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetAvailableRolesSuccess, FBeamRequestContext, Context, UGetAvailableRolesRequest*, Request, UAvailableRolesResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetAvailableRolesError, FBeamRequestContext, Context, UGetAvailableRolesRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetAvailableRolesComplete, FBeamRequestContext, Context, UGetAvailableRolesRequest*, Request);

using FGetAvailableRolesFullResponse = FBeamFullResponse<UGetAvailableRolesRequest*, UAvailableRolesResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetAvailableRolesFullResponse, FGetAvailableRolesFullResponse);
