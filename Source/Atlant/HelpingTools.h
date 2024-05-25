#pragma once

#include "CoreMinimal.h"

namespace Help
{
	template <typename FmtType, typename... Types>
	void DisplayDebugMessage(const FmtType& Fmt, Types... Args)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(Fmt, Args...));
		}
	}

	template <typename FmtType, typename... Types>
	void DisplayErrorMessage(const FmtType& Fmt, Types... Args)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(Fmt, Args...));
		}
	}
}