
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"


#include "AutoGen/CommonResponse.h"

#include "PutRefreshRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutRefreshRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UPutRefreshRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Events", DisplayName="Beam - Make PutRefresh",  meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UPutRefreshRequest* Make(int64 _ObjectId, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutRefreshSuccess, FBeamRequestContext, Context, UPutRefreshRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutRefreshError, FBeamRequestContext, Context, UPutRefreshRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutRefreshComplete, FBeamRequestContext, Context, UPutRefreshRequest*, Request);

using FPutRefreshFullResponse = FBeamFullResponse<UPutRefreshRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPutRefreshFullResponse, FPutRefreshFullResponse);
