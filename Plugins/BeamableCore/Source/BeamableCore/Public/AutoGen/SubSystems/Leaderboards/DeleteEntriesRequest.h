
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/CommonResponse.h"

#include "DeleteEntriesRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteEntriesRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	FString ObjectId;
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UDeleteEntriesRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UDeleteEntriesRequest* MakeDeleteEntriesRequest(FString _ObjectId, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteEntriesSuccess, FBeamRequestContext, Context, UDeleteEntriesRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteEntriesError, FBeamRequestContext, Context, UDeleteEntriesRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteEntriesComplete, FBeamRequestContext, Context, UDeleteEntriesRequest*, Request);

using FDeleteEntriesFullResponse = FBeamFullResponse<UDeleteEntriesRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnDeleteEntriesFullResponse, FDeleteEntriesFullResponse);
