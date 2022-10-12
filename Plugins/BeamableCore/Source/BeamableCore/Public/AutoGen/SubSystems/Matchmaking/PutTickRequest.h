
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/EmptyResponse.h"

#include "PutTickRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutTickRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UPutTickRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UPutTickRequest* MakePutTickRequest(int64 _ObjectId, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutTickSuccess, FBeamRequestContext, Context, UPutTickRequest*, Request, UEmptyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutTickError, FBeamRequestContext, Context, UPutTickRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutTickComplete, FBeamRequestContext, Context, UPutTickRequest*, Request);

using FPutTickFullResponse = FBeamFullResponse<UPutTickRequest*, UEmptyResponse*>;
DECLARE_DELEGATE_OneParam(FOnPutTickFullResponse, FPutTickFullResponse);