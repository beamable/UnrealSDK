
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/MultipliersGetResponse.h"

#include "GetMultipliersRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetMultipliersRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetMultipliersRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UGetMultipliersRequest* MakeGetMultipliersRequest(int64 _ObjectId, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetMultipliersSuccess, FBeamRequestContext, Context, UGetMultipliersRequest*, Request, UMultipliersGetResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetMultipliersError, FBeamRequestContext, Context, UGetMultipliersRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetMultipliersComplete, FBeamRequestContext, Context, UGetMultipliersRequest*, Request);

using FGetMultipliersFullResponse = FBeamFullResponse<UGetMultipliersRequest*, UMultipliersGetResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetMultipliersFullResponse, FGetMultipliersFullResponse);