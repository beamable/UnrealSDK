
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/CommonResponse.h"

#include "PutFreezeRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutFreezeRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	FString ObjectId;
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UPutFreezeRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UPutFreezeRequest* MakePutFreezeRequest(FString _ObjectId, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutFreezeSuccess, FBeamRequestContext, Context, UPutFreezeRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutFreezeError, FBeamRequestContext, Context, UPutFreezeRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutFreezeComplete, FBeamRequestContext, Context, UPutFreezeRequest*, Request);

using FPutFreezeFullResponse = FBeamFullResponse<UPutFreezeRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPutFreezeFullResponse, FPutFreezeFullResponse);
